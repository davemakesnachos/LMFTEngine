cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# set the project name
project(LMFTEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_library(LMFTEngine STATIC ${CMAKE_SOURCE_DIR}/src/logger.cpp
                            ${CMAKE_SOURCE_DIR}/src/window.cpp
                            ${CMAKE_SOURCE_DIR}/src/main.cpp
                            ${CMAKE_SOURCE_DIR}/src/eventmanager.cpp
                            ${CMAKE_SOURCE_DIR}/src/game.cpp
                            ${CMAKE_SOURCE_DIR}/src/gamelogic.cpp
                            ${CMAKE_SOURCE_DIR}/src/entity.cpp
                            ${CMAKE_SOURCE_DIR}/src/entityfactory.cpp
                            ${CMAKE_SOURCE_DIR}/src/component/physicsbox2d_component.cpp
                            ${CMAKE_SOURCE_DIR}/src/component/transform2d_component.cpp
                            ${CMAKE_SOURCE_DIR}/src/physics/physicsbox2d.cpp
)

add_subdirectory(app/1-pong)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(box2d REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIRS})

set_target_properties(LMFTEngine PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(LMFTEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} box2d)
