#ifndef PSISWARM_WHEELS_DEFAULT_ACTUATOR_H
#define PSISWARM_WHEELS_DEFAULT_ACTUATOR_H

namespace argos
{
    class CPsiSwarmWheelsDefaultActuator;
}

#include <argos3/plugins/robots/psi-swarm/control_interface/ci_psiswarm_wheels_actuator.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>
#include <argos3/core/simulator/actuator.h>
#include <argos3/core/utility/math/rng.h>

namespace argos
{
    class CPsiSwarmWheelsDefaultActuator : public CSimulatedActuator, public CCI_PsiSwarmWheelsActuator
    {
    public:

        enum DIFFERENTIAL_STEERING
        {
            LEFT_WHEEL = 0,
            RIGHT_WHEEL = 1
        };

        CPsiSwarmWheelsDefaultActuator();
        virtual ~CPsiSwarmWheelsDefaultActuator() {}

        virtual void Init(TConfigurationNode& t_tree);
        virtual void SetRobot(CComposableEntity& c_entity);
        virtual void Update();
        virtual void Reset();

        virtual void SetLinearVelocity(Real f_left_velocity, Real f_right_velocity);

    private:

        virtual void AddGaussianNoise();

        CWheeledEntity* m_pcWheeledEntity;
        Real m_fCurrentVelocity[2];

        CRandom::CRNG* m_pcRNG;
        Real m_fNoiseStdDeviation;
   };
}

#endif
