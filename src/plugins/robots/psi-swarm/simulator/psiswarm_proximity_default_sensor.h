#ifndef PSISWARM_PROXIMITY_DEFAULT_SENSOR_H
#define PSISWARM_PROXIMITY_DEFAULT_SENSOR_H

namespace argos
{
    class CPsiSwarmProximityDefaultSensor;
}

#include <argos3/plugins/robots/psi-swarm/control_interface/ci_psiswarm_proximity_sensor.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>

namespace argos
{
    class CPsiSwarmProximityDefaultSensor : public CSimulatedSensor, public CCI_PsiSwarmProximitySensor
    {

    public:

        CPsiSwarmProximityDefaultSensor();
        virtual ~CPsiSwarmProximityDefaultSensor() {}

        virtual void SetRobot(CComposableEntity& c_entity);
        virtual void Init(TConfigurationNode& t_tree);
        virtual void Update();
        virtual void Reset();

        virtual Real CalculateReading(Real f_distance);

    private:

        CEmbodiedEntity* m_pcEmbodiedEntity;
        CProximitySensorEquippedEntity* m_pcProximityEntity;
        CControllableEntity* m_pcControllableEntity;

        bool m_bShowRays;
        CRandom::CRNG* m_pcRNG;

        bool m_bAddNoise;
        CRange<Real> m_cNoiseRange;

        CSpace& m_cSpace;
   };
}

#endif
