#ifndef DYNAMICS2D_PSISWARM_MODEL_H
#define DYNAMICS2D_PSISWARM_MODEL_H

namespace argos
{
    class CDynamics2DDifferentialSteeringControl;
}

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_single_body_object_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_differentialsteering_control.h>
#include <argos3/plugins/robots/psi-swarm/simulator/psiswarm_entity.h>

namespace argos
{
    class CDynamics2DPsiSwarmModel : public CDynamics2DSingleBodyObjectModel
    {
    public:

        CDynamics2DPsiSwarmModel(CDynamics2DEngine& c_engine, CPsiSwarmEntity& c_entity);
        virtual ~CDynamics2DPsiSwarmModel();

        virtual void Reset();
        virtual void UpdateFromEntityStatus();

    private:

        CPsiSwarmEntity& m_cPsiSwarmEntity;
        CWheeledEntity& m_cWheeledEntity;

        CDynamics2DDifferentialSteeringControl m_cDiffSteering;
        const Real* m_fCurrentWheelVelocity;
   };
}

#endif
