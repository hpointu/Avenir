cmake_minimum_required(VERSION 2.6)
project(Avenir)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
add_definitions(-DAV_DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SFML REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})

include_directories(/usr/lib/gcc/i686-pc-linux-gnu/4.4.5/include/g++-v4/)

include_directories(/usr/local/include/)

set(mainLibs ${SFML_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLUT_LIBRARIES})

add_subdirectory(src/)


