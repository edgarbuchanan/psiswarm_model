set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_CONTROLINTERFACE
  control_interface/ci_psiswarm_proximity_sensor.h
  control_interface/ci_psiswarm_wheels_actuator.h)
# argos3/plugins/robots/psiswarm/simulator
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR
    simulator/dynamics2d_psiswarm_model.h
    simulator/psiswarm_entity.h
    simulator/psiswarm_proximity_default_sensor.h
    simulator/psiswarm_wheels_default_actuator.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# psiswarm sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_CONTROLINTERFACE}
  control_interface/ci_psiswarm_proximity_sensor.cpp
  control_interface/ci_psiswarm_wheels_actuator.cpp)

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR}
    simulator/dynamics2d_psiswarm_model.cpp
    simulator/psiswarm_entity.cpp
    simulator/psiswarm_proximity_default_sensor.cpp
    simulator/psiswarm_wheels_default_actuator.cpp)
  # Compile the graphical visualization only if the necessary libraries have been found
  if(ARGOS_QTOPENGL_FOUND)
    include_directories(${ARGOS_QTOPENGL_INCLUDE_DIRS})
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR}
      simulator/qtopengl_psiswarm.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM}
      simulator/qtopengl_psiswarm.h
      simulator/qtopengl_psiswarm.cpp)
  endif(ARGOS_QTOPENGL_FOUND)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Create psiswarm plugin
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_psiswarm SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_psiswarm
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
  argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d
  argos3plugin_${ARGOS_BUILD_FOR}_pointmass3d)
if(ARGOS_QTOPENGL_FOUND)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_psiswarm argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
  if(RT_FOUND)
    target_link_libraries(argos3plugin_simulator_psiswarm ${RT_LIBRARY})
  endif(RT_FOUND)
endif(ARGOS_QTOPENGL_FOUND)

#
# Create kilolib
#
#if(ARGOS_BUILD_FOR_SIMULATOR)
#  add_library(argos3plugin_simulator_psilib
#    control_interface/psilib.c
#    control_interface/message_crc.c)
#  if(RT_FOUND)
#    target_link_libraries(argos3plugin_simulator_psilib ${RT_LIBRARY})
#  endif(RT_FOUND)
#endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Installation
#
install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/psi-swarm/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR}      DESTINATION include/argos3/plugins/robots/psi-swarm/simulator)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_psiswarm
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(TARGETS 
#argos3plugin_simulator_psilib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/argos3
    ARCHIVE DESTINATION lib/argos3)
endif(ARGOS_BUILD_FOR_SIMULATOR)
