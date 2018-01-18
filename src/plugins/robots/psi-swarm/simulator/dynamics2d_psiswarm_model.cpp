#include "dynamics2d_psiswarm_model.h"
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos
{
    enum PSISWARM_WHEELS
    {
        PSISWARM_LEFT_WHEEL = 0,
        PSISWARM_RIGHT_WHEEL = 1
    };

    CDynamics2DPsiSwarmModel::CDynamics2DPsiSwarmModel(CDynamics2DEngine& c_engine, CPsiSwarmEntity& c_entity):
            CDynamics2DSingleBodyObjectModel(c_engine, c_entity),
            m_cPsiSwarmEntity(c_entity),
            m_cWheeledEntity(m_cPsiSwarmEntity.GetWheeledEntity()),
            m_cDiffSteering(c_engine,
                            CPsiSwarmEntity::MAX_FORCE,
                            CPsiSwarmEntity::MAX_TORQUE,
                            CPsiSwarmEntity::INTERWHEEL_DISTANCE),
            m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities())
    {
        // Create the body with initial position and orientation
        cpBody* ptBody = cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                                        cpBodyNew(CPsiSwarmEntity::MASS,
                                                  cpMomentForCircle(CPsiSwarmEntity::MASS,
                                                                    0.0f,
                                                                    CPsiSwarmEntity::BODY_RADIUS + CPsiSwarmEntity::BODY_RADIUS,
                                                                    cpvzero)));

        const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
        ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
        CRadians cXAngle, cYAngle, cZAngle;
        GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
        cpBodySetAngle(ptBody, cZAngle.GetValue());

        // Create the body shape
        cpShape* ptShape = cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                                           cpCircleShapeNew(ptBody,
                                                            CPsiSwarmEntity::BODY_RADIUS,
                                                            cpvzero));
        ptShape->e = 0.0; // No elasticity
        ptShape->u = 0.7; // Lots of friction

        // Constrain the actual base body to follow the differential steering control
        m_cDiffSteering.AttachTo(ptBody);

        // Set the body so that the default methods work as expected
        SetBody(ptBody, CPsiSwarmEntity::BODY_HEIGHT);
    }

    CDynamics2DPsiSwarmModel::~CDynamics2DPsiSwarmModel()
    {
        m_cDiffSteering.Detach();
    }

    void CDynamics2DPsiSwarmModel::Reset()
    {
        CDynamics2DSingleBodyObjectModel::Reset();
        m_cDiffSteering.Reset();
    }

    void CDynamics2DPsiSwarmModel::UpdateFromEntityStatus()
    {
        // Do we want to move?
        if((m_fCurrentWheelVelocity[PSISWARM_LEFT_WHEEL] != 0.0f) ||
           (m_fCurrentWheelVelocity[PSISWARM_RIGHT_WHEEL] != 0.0f))
        {
            m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[PSISWARM_LEFT_WHEEL],
                                             m_fCurrentWheelVelocity[PSISWARM_RIGHT_WHEEL]);
        }
        else
        {
            // No, we don't want to move - zero all speeds
            m_cDiffSteering.Reset();
        }
    }

    REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CPsiSwarmEntity, CDynamics2DPsiSwarmModel);
}
