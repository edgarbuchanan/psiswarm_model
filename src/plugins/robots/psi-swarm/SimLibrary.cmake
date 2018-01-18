#
# psi-swarm simulator code
#
# Headers
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR
  simulator/dynamics2d_psiswarm_model.h
  simulator/psiswarm_entity.h
  simulator/psiswarm_wheels_default_actuator.h
  simulator/psiswarm_proximity_default_sensor.h)
if(ARGOS_COMPILE_QTOPENGL)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR}
    simulator/qtopengl_psiswarm.h)
endif(ARGOS_COMPILE_QTOPENGL)

# Install location for the psi-swarm simulator headers
install(
  FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR}
  DESTINATION include/argos3/plugins/robots/psi-swarm/simulator)

# Sources
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM
  ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM}
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_SIMULATOR}
  simulator/dynamics2d_psiswarm_model.cpp
  simulator/psiswarm_entity.cpp
  simulator/psiswarm_wheels_default_actuator.cpp
  simulator/psiswarm_proximity_default_sensor.cpp)
if(ARGOS_COMPILE_QTOPENGL)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM}
    simulator/qtopengl_psiswarm.cpp)
endif(ARGOS_COMPILE_QTOPENGL)

#
# Create psi-swarm plugin
#
# Create target
add_library(argos3plugin_${ARGOS_BUILD_FOR}_psiswarm SHARED
  ${ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM})
# Link libraries
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_psiswarm
  argos3core_${ARGOS_BUILD_FOR}
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
  argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d)
if(ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_psiswarm
    argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
endif(ARGOS_COMPILE_QTOPENGL)

# Install location for the psi-swarm plugin
install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_psiswarm
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
