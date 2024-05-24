cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(MC_X17_Germanium_Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES ${PROJECT_SOURCE_DIR}/macros/*.mac)

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(mc_germanium mc_germanium.cc ${sources} ${headers})
target_link_libraries(mc_germanium ${Geant4_LIBRARIES})

add_custom_target(MC_X17_Germanium_Simulation DEPENDS mc_germanium)