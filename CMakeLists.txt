cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# set the project name
project(LMFTEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# add the executable
add_executable(LMFTEngine ${CMAKE_SOURCE_DIR}/src/logger.cpp
                            ${CMAKE_SOURCE_DIR}/src/window.cpp
                            ${CMAKE_SOURCE_DIR}/src/main.cpp
                            ${CMAKE_SOURCE_DIR}/src/game.cpp
                            ${CMAKE_SOURCE_DIR}/src/entity.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set_target_properties(LMFTEngine PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(LMFTEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
