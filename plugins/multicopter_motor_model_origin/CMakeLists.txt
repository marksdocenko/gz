cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

find_package(gz-cmake3 REQUIRED)

project(SampleSystem)

find_package(gz-plugin2 REQUIRED COMPONENTS register)
set(GZ_PLUGIN_VER ${gz-plugin2_VERSION_MAJOR})

find_package(gz-sim7 REQUIRED)
add_library(MulticopterMotorModelOrigin SHARED MulticopterMotorModelOrigin.cc)
set_property(TARGET MulticopterMotorModelOrigin PROPERTY CXX_STANDARD 17)
target_link_libraries(MulticopterMotorModelOrigin
  PRIVATE gz-plugin${GZ_PLUGIN_VER}::gz-plugin${GZ_PLUGIN_VER}
  PRIVATE gz-sim7::gz-sim7)
