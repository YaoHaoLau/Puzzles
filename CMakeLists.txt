CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(Puzzles C CXX)

SET(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_STANDARD 11)

ADD_COMPILE_OPTIONS(-Wall -fno-strict-aliasing)

ENABLE_TESTING()

IF(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  MESSAGE("Setting build type to 'RelWithDebInfo' as none was specified.")
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
ENDIF()

ADD_SUBDIRECTORY(leetcode)

