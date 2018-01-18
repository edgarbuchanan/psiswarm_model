#include "ci_psiswarm_proximity_sensor.h"
#include "../simulator/psiswarm_entity.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos
{
    CCI_PsiSwarmProximitySensor::CCI_PsiSwarmProximitySensor():
            m_tReadings(8)
    {
        // Set the values for the proximity sensor angles
        m_tReadings[0].Angle = CPsiSwarmEntity::PROXIMITY_SENSOR_RING_START_ANGLE;

        for(int i = 1; i < 8; i++)
            m_tReadings[i].Angle = m_tReadings[i-1].Angle + CPsiSwarmEntity::PROXIMITY_SENSOR_RING_INTERVAL_ANGLE;
    }

    #ifdef ARGOS_WITH_LUA
    void CCI_PsiSwarmProximitySensor::CreateLuaState(lua_State* pt_lua_state)
    {
        CLuaUtility::OpenRobotStateTable(pt_lua_state, "proximity");

        for(size_t i = 0; i < GetReadings().size(); ++i)
        {
            CLuaUtility::StartTable(pt_lua_state, i+1);
            CLuaUtility::AddToTable(pt_lua_state, "angle", m_tReadings[i].Angle);
            CLuaUtility::AddToTable(pt_lua_state, "value", m_tReadings[i].Value);
            CLuaUtility::EndTable  (pt_lua_state);
        }

        CLuaUtility::CloseRobotStateTable(pt_lua_state);
    }
    #endif

    #ifdef ARGOS_WITH_LUA
    void CCI_PsiSwarmProximitySensor::ReadingsToLuaState(lua_State* pt_lua_state)
    {
        lua_getfield(pt_lua_state, -1, "proximity");

        for(size_t i = 0; i < GetReadings().size(); ++i)
        {
            lua_pushnumber(pt_lua_state, i+1);
            lua_gettable  (pt_lua_state, -2);
            lua_pushnumber(pt_lua_state, m_tReadings[i].Value);
            lua_setfield  (pt_lua_state, -2, "value");
            lua_pop(pt_lua_state, 1);
        }

        lua_pop(pt_lua_state, 1);
    }
    #endif

    std::ostream& operator << (std::ostream& c_os, const CCI_PsiSwarmProximitySensor::SReading& s_reading)
    {
        c_os << "SReading("
             << s_reading.Value << ","
             << s_reading.Angle << ")";

        return c_os;
    }

    std::ostream& operator << (std::ostream& c_os, const CCI_PsiSwarmProximitySensor::TReadings& t_readings)
    {
        if(!t_readings.empty())
        {
            c_os << t_readings[0];

            for(UInt16 i = 1; i < t_readings.size(); ++i)
                c_os << " " << t_readings[i];
        }

        return c_os;
    }
}
