#ifndef PSISWARM_ENTITY_H
#define PSISWARM_ENTITY_H

namespace argos
{
    class CControllableEntity;
    class CEmbodiedEntity;
    class CPsiSwarmEntity;
    class CProximitySensorEquippedEntity;
}

#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>

namespace argos
{
    class CPsiSwarmEntity : public CComposableEntity
    {

    public:

        ENABLE_VTABLE();

    public:

        CPsiSwarmEntity();

        CPsiSwarmEntity(const std::string& str_id,
                        const std::string& str_controller_id,
                        const CVector3& c_position = CVector3(),
                        const CQuaternion& c_orientation = CQuaternion());

        virtual void Init(TConfigurationNode& t_tree);
        virtual void Reset();
        virtual void Destroy();

        virtual void UpdateComponents();

        inline CControllableEntity& GetControllableEntity()
        {
            return *m_pcControllableEntity;
        }

        inline CEmbodiedEntity& GetEmbodiedEntity()
        {
            return *m_pcEmbodiedEntity;
        }

        inline CProximitySensorEquippedEntity& GetProximitySensorEquippedEntity()
        {
            return *m_pcProximitySensorEquippedEntity;
        }

        inline CWheeledEntity& GetWheeledEntity()
        {
            return *m_pcWheeledEntity;
        }

        virtual std::string GetTypeDescription() const
        {
            return "psiswarm";
        }

    private:

        CControllableEntity*            m_pcControllableEntity;
        CEmbodiedEntity*                m_pcEmbodiedEntity;
        CProximitySensorEquippedEntity* m_pcProximitySensorEquippedEntity;
        CWheeledEntity*                 m_pcWheeledEntity;

    public:

        static const Real BODY_RADIUS;
        static const Real BODY_HEIGHT;
        static const Real BODY_ELEVATION;

        static const Real WHEEL_DIAMETER;
        static const Real WHEEL_RADIUS;
        static const Real WHEEL_WIDTH;
        static const Real HALF_WHEEL_WIDTH;
        static const Real INTERWHEEL_DISTANCE;
        static const Real HALF_INTERWHEEL_DISTANCE;

        static const Real PROXIMITY_SENSOR_RING_ELEVATION;
        static const Real PROXIMITY_SENSOR_RING_RADIUS;
        static const CRadians PROXIMITY_SENSOR_RING_START_ANGLE;
        static const CRadians PROXIMITY_SENSOR_RING_INTERVAL_ANGLE;
        static const Real PROXIMITY_SENSOR_RING_RANGE;

        static const Real MASS;
        static const Real MAX_FORCE;
        static const Real MAX_TORQUE;
    };
}

#endif
