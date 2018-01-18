#ifndef CCI_PSISWARM_WHEELS_ACTUATOR_H
#define CCI_PSISWARM_WHEELS_ACTUATOR_H

namespace argos
{
   class CCI_PsiSwarmWheelsActuator;
}

#include <argos3/core/control_interface/ci_actuator.h>
#include <argos3/core/utility/logging/argos_log.h>

namespace argos
{
    class CCI_PsiSwarmWheelsActuator : virtual public CCI_Actuator
    {
    public:

        static const Real MAX_VELOCITY_CM_SEC; // Maximum linear speed for the wheels in cm/sec
        static const Real MIN_VELOCITY_CM_SEC; // Minimum linear speed for the wheels in cm/sec

        virtual void SetLinearVelocity(Real f_left_velocity, Real f_right_velocity) = 0;

        #ifdef ARGOS_WITH_LUA
        virtual void CreateLuaState(lua_State* pt_lua_state);
        #endif
    };
}

#endif
