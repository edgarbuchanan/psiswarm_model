#
# psi-swarm control interface headers
#
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_CONTROLINTERFACE
  # Sensors
  control_interface/ci_psiswarm_proximity_sensor.h
  # Actuators
  control_interface/ci_psiswarm_wheels_actuator.h)

#
# psi-swarm control interface sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_PSISWARM
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_CONTROLINTERFACE}
  # Sensors
  control_interface/ci_psiswarm_proximity_sensor.cpp
  # Actuators
  control_interface/ci_psiswarm_wheels_actuator.cpp)

#
# Install location for the psi-swarm control interface headers
#
install(
  FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_PSISWARM_CONTROLINTERFACE}
  DESTINATION include/argos3/plugins/robots/psi-swarm/control_interface)
