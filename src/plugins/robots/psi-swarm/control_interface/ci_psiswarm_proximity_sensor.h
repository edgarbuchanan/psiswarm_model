#ifndef CCI_PSISWARM_PROXIMITY_SENSOR_H
#define CCI_PSISWARM_PROXIMITY_SENSOR_H

namespace argos
{
   class CCI_PsiSwarmProximitySensor;
}

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/config.h>

namespace argos
{
    class CCI_PsiSwarmProximitySensor : public CCI_Sensor
    {
    public:

        // Single sensor reading
        struct SReading
        {
            Real Value; // Value of the reading
            CRadians Angle; // Angle of the reading

            SReading():
                    Value(0.0f) {}

            SReading(Real f_value, const CRadians& c_angle):
                    Value(f_value),
                    Angle(c_angle) {}
        };

        // Sensor ring readings
        typedef std::vector<SReading> TReadings;

        CCI_PsiSwarmProximitySensor();
        virtual ~CCI_PsiSwarmProximitySensor() {}

        inline const TReadings& GetReadings() const
        {
            return m_tReadings;
        }

        inline const SReading& GetReading(UInt16 i) const
        {
            return m_tReadings[i];
        }

        #ifdef ARGOS_WITH_LUA
        virtual void CreateLuaState(lua_State* pt_lua_state);
        virtual void ReadingsToLuaState(lua_State* pt_lua_state);
        #endif

    protected:

          TReadings m_tReadings;
    };

    // Redefine the "<<" operator for one reading
    std::ostream& operator<<(std::ostream& c_os, const CCI_PsiSwarmProximitySensor::SReading& s_reading);

    // Redefine the "<<" operator for multiple readings
    std::ostream& operator<<(std::ostream& c_os, const CCI_PsiSwarmProximitySensor::TReadings& t_readings);
}

#endif
