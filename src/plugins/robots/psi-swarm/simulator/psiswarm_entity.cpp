#include "psiswarm_entity.h"

#include <argos3/core/utility/math/matrix/rotationmatrix3.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>

#include <argos3/core/utility/math/general.h>

namespace argos
{
    const Real CPsiSwarmEntity::BODY_RADIUS    = 0.054f;
    const Real CPsiSwarmEntity::BODY_HEIGHT    = 0.037f;
    const Real CPsiSwarmEntity::BODY_ELEVATION = 0.008f;

    const Real CPsiSwarmEntity::WHEEL_DIAMETER           = 0.032f;
    const Real CPsiSwarmEntity::WHEEL_RADIUS             = WHEEL_DIAMETER * 0.5f;
    const Real CPsiSwarmEntity::WHEEL_WIDTH              = 0.008f;
    const Real CPsiSwarmEntity::HALF_WHEEL_WIDTH         = WHEEL_WIDTH * 0.5f;
    const Real CPsiSwarmEntity::INTERWHEEL_DISTANCE      = 0.103f;
    const Real CPsiSwarmEntity::HALF_INTERWHEEL_DISTANCE = INTERWHEEL_DISTANCE * 0.5f;

    const Real     CPsiSwarmEntity::PROXIMITY_SENSOR_RING_ELEVATION      = 0.013f;
    const Real     CPsiSwarmEntity::PROXIMITY_SENSOR_RING_RADIUS         = BODY_RADIUS + 0.001;
    const CRadians CPsiSwarmEntity::PROXIMITY_SENSOR_RING_START_ANGLE    = ToRadians(CDegrees(22.5));
    const CRadians CPsiSwarmEntity::PROXIMITY_SENSOR_RING_INTERVAL_ANGLE = ToRadians(CDegrees(45));
    const Real     CPsiSwarmEntity::PROXIMITY_SENSOR_RING_RANGE          = 0.05f;

    const Real CPsiSwarmEntity::MASS       = 0.4f;
    const Real CPsiSwarmEntity::MAX_FORCE  = 1.5f;
    const Real CPsiSwarmEntity::MAX_TORQUE = 1.5f;

    CPsiSwarmEntity::CPsiSwarmEntity():
            CComposableEntity(NULL),
            m_pcControllableEntity(NULL),
            m_pcEmbodiedEntity(NULL),
            m_pcProximitySensorEquippedEntity(NULL),
            m_pcWheeledEntity(NULL) {}

    CPsiSwarmEntity::CPsiSwarmEntity(const std::string& str_id,
                                     const std::string& str_controller_id,
                                     const CVector3& c_position,
                                     const CQuaternion& c_orientation):
            CComposableEntity(NULL, str_id),
            m_pcControllableEntity(NULL),
            m_pcEmbodiedEntity(NULL),
            m_pcProximitySensorEquippedEntity(NULL),
            m_pcWheeledEntity(NULL)
    {
        try
        {
            // Create and initialise components

            // Embodied entity
            m_pcEmbodiedEntity = new CEmbodiedEntity(this, "body_0", c_position, c_orientation);
            AddComponent(*m_pcEmbodiedEntity);

            // Wheeled entity and wheel positions (left, right)
            m_pcWheeledEntity = new CWheeledEntity(this, "wheels_0", 2);
            AddComponent(*m_pcWheeledEntity);
            m_pcWheeledEntity->SetWheel(0, CVector3(0.0f,  HALF_INTERWHEEL_DISTANCE, 0.0f), WHEEL_RADIUS);
            m_pcWheeledEntity->SetWheel(1, CVector3(0.0f, -HALF_INTERWHEEL_DISTANCE, 0.0f), WHEEL_RADIUS);

            // Proximity sensor equipped entity
            m_pcProximitySensorEquippedEntity = new CProximitySensorEquippedEntity(this, "proximity_0");
            AddComponent(*m_pcProximitySensorEquippedEntity);
            m_pcProximitySensorEquippedEntity->AddSensorRing(
                    CVector3(0.0f, 0.0f, PROXIMITY_SENSOR_RING_ELEVATION),
                    PROXIMITY_SENSOR_RING_RADIUS,
                    PROXIMITY_SENSOR_RING_START_ANGLE,
                    PROXIMITY_SENSOR_RING_RANGE,
                    8,
                    m_pcEmbodiedEntity->GetOriginAnchor());

            // Controllable entity (it must be the last one, for actuators/sensors to link to composing entities correctly)
            m_pcControllableEntity = new CControllableEntity(this, "controller_0");
            AddComponent(*m_pcControllableEntity);
            m_pcControllableEntity->SetController(str_controller_id);

            // Update components
            UpdateComponents();
        }
        catch(CARGoSException& ex)
        {
            LOG << ex.what() << "\n";
            THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
        }
    }

    void CPsiSwarmEntity::Init(TConfigurationNode& t_tree)
    {
        try
        {
            // Initialise parent
            CComposableEntity::Init(t_tree);

            // Create and initialise components

            // Embodied entity
            m_pcEmbodiedEntity = new CEmbodiedEntity(this);
            AddComponent(*m_pcEmbodiedEntity);
            m_pcEmbodiedEntity->Init(GetNode(t_tree, "body"));

            // Wheeled entity and wheel positions (left, right)
            m_pcWheeledEntity = new CWheeledEntity(this, "wheels_0", 2);
            AddComponent(*m_pcWheeledEntity);
            m_pcWheeledEntity->SetWheel(0, CVector3(0.0f,  HALF_INTERWHEEL_DISTANCE, 0.0f), WHEEL_RADIUS);
            m_pcWheeledEntity->SetWheel(1, CVector3(0.0f, -HALF_INTERWHEEL_DISTANCE, 0.0f), WHEEL_RADIUS);

            // Proximity sensor equipped entity
            m_pcProximitySensorEquippedEntity = new CProximitySensorEquippedEntity(this, "proximity_0");
            AddComponent(*m_pcProximitySensorEquippedEntity);
            m_pcProximitySensorEquippedEntity->AddSensorRing(
                    CVector3(0.0f, 0.0f, PROXIMITY_SENSOR_RING_ELEVATION),
                    PROXIMITY_SENSOR_RING_RADIUS,
                    PROXIMITY_SENSOR_RING_START_ANGLE,
                    PROXIMITY_SENSOR_RING_RANGE,
                    8,
                    m_pcEmbodiedEntity->GetOriginAnchor());

            // Controllable entity (it must be the last one, for actuators/sensors to link to composing entities correctly)
            m_pcControllableEntity = new CControllableEntity(this);
            AddComponent(*m_pcControllableEntity);
            m_pcControllableEntity->Init(GetNode(t_tree, "controller"));

            // Update components
            UpdateComponents();
        }
        catch(CARGoSException& ex)
        {
            LOG << ex.what() << "\n";
            THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
        }
    }

    void CPsiSwarmEntity::Reset()
    {
        // Reset all components
        CComposableEntity::Reset();
        // Update components
        UpdateComponents();
    }

    void CPsiSwarmEntity::Destroy()
    {
        CComposableEntity::Destroy();
    }

    #define UPDATE(COMPONENT) if(COMPONENT->IsEnabled()) COMPONENT->Update();

    void CPsiSwarmEntity::UpdateComponents()
    {

    }

    REGISTER_ENTITY(CPsiSwarmEntity,
                    "psi-swarm",
                    "York Robotics Laboratory",
                    "1.0",
                    "The Psi Swarm robot",
                    "The Psi Swarm robot is a new platform developed at the York Robotics Laboratory that\n"
                    "is designed to allow low-cost swarms of robots to be assembled for use in research,\n"
                    "teaching and outreach. More information is available at https://www.york.ac.uk/robot-lab/psiswarm\n\n"
                    "REQUIRED XML CONFIGURATION\n\n"
                    "  <arena ...>\n"
                    "    ...\n"
                    "    <psi-swarm id=\"ps0\">\n"
                    "      <body position=\"0,0,0\" orientation=\"0,0,0\"/>\n"
                    "      <controller config=\"my_controller\"/>\n"
                    "    </psi-swarm>\n"
                    "    ...\n"
                    "  </arena>\n\n"
                    "The 'id' attribute is necessary and must be unique among the entities. If two\n"
                    "entities share the same id, initialization aborts.\n"
                    "The 'body/position' attribute specifies the position of the bottom point of the\n"
                    "Psi Swarm in the arena. When the robot is untranslated and unrotated, the\n"
                    "bottom point is in the origin and it is defined as the middle point between\n"
                    "the two wheels on the XY plane and the lowest point of the robot on the Z\n"
                    "axis, that is the point where the wheels touch the floor. The attribute values\n"
                    "are in the X,Y,Z order.\n"
                    "The 'body/orientation' attribute specifies the orientation of the Psi Swarm. All\n"
                    "rotations are performed with respect to the pucktom point. The order of the\n"
                    "angles is Z,Y,X, which means that the first number corresponds to the rotation\n"
                    "around the Z axis, the second around Y and the last around X. This reflects\n"
                    "the internal convention used in ARGoS, in which rotations are performed in\n"
                    "that order. Angles are expressed in degrees. When the robot is unrotated, it\n"
                    "is oriented along the X axis.\n"
                    "The 'controller/config' attribute is used to assign a controller to the\n"
                    "psi-swarm. The value of the attribute must be set to the id of a previously\n"
                    "defined controller. Controllers are defined in the <controllers> XML subtree.\n\n"
                    "OPTIONAL XML CONFIGURATION\n\n"
                    "None for the time being.\n",
                    "Under development"
                    );

    REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CPsiSwarmEntity);
}
