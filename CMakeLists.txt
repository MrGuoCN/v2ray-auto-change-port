cmake_minimum_required(VERSION 3.0)
project(v2ray-auto-change-port "CXX")
set(CMAKE_CXX_STANDARD 20)
set(HOME ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(v2ray-auto-change-port ${SRC_LIST})

