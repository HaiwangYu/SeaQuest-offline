# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(phgenfit CXX C)

# source code
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)

# ROOT
find_program(ROOTCONF "root-config")
if(ROOTCONF)
  message("-- Detecting ROOT:    found at ${ROOTCONF}")
else()
  message(FATAL_ERROR "-- Detecting ROOT:    not found")
endif()
execute_process(COMMAND root-config --prefix OUTPUT_VARIABLE ROOT_PREFIX  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CFLAGS  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND root-config --libs   OUTPUT_VARIABLE ROOT_LINK    OUTPUT_STRIP_TRAILING_WHITESPACE)


# Geant4
find_program(G4CONF "geant4-config")
if(G4CONF)
  message("-- Detecting Geant4:  found at ${G4CONF}")
else()
  message(FATAL_ERROR "-- Detecting Geant4:  not found")
endif()
#find_package(Geant4 REQUIRED vis_all)
execute_process(COMMAND geant4-config --cflags OUTPUT_VARIABLE GEANT4_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND geant4-config --libs   OUTPUT_VARIABLE GEANT4_LINK   OUTPUT_STRIP_TRAILING_WHITESPACE)

# Warning suppression
string(REGEX REPLACE "-W[a-z-]*" "" GEANT4_CFLAGS ${GEANT4_CFLAGS})
string(REPLACE "-pedantic" "" GEANT4_CFLAGS ${GEANT4_CFLAGS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GEANT4_CFLAGS} ${ROOT_CFLAGS} -std=c++11 ")
message("CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})

add_library(phgenfit SHARED ${sources})
target_link_libraries(phgenfit -lgenfit2 -lgenfitexp -lphfield)

install(TARGETS phgenfit 					DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

message(${CMAKE_PROJECT_NAME} " will be installed to " ${CMAKE_INSTALL_PREFIX})

file(GLOB dist_headers
  ${PROJECT_SOURCE_DIR}/Fitter.h
  ${PROJECT_SOURCE_DIR}/Measurement.h
  ${PROJECT_SOURCE_DIR}/PlanarMeasurement.h
  ${PROJECT_SOURCE_DIR}/SpacepointMeasurement.h
  ${PROJECT_SOURCE_DIR}/Track.h
  ${PROJECT_SOURCE_DIR}/Tools.h
)
install(FILES ${dist_headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}/)
