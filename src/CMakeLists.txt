cmake_minimum_required(VERSION 2.8)

# Deactivate RPATH for MacOSX
set(CMAKE_MACOSX_RPATH 0)

# Set the path where CMake will find additional scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# Set build options
set(ARGOS_BUILD_FOR "simulator")
set(ARGOS_BUILD_FOR_SIMULATOR TRUE)

# Set compiler flags
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildFlags.cmake)

# Find the ARGoS package, make sure to save the ARGoS prefix
find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_simulator)
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)

# Check for Lua 5.2
find_package(Lua52 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# Check for Qt and OpenGL
include(ARGoSCheckQTOpenGL)

# Set up ARGoS compilation information
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
link_directories(${ARGOS_LIBRARY_DIRS})

# Descend into the plugins directory
add_subdirectory(plugins)
