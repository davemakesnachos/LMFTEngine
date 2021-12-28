cmake_minimum_required(VERSION 3.1)

add_executable(pong ponggamelogic.cpp)
target_link_libraries(pong LMFTEngine)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
