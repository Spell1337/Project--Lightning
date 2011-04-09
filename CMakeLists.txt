project(lightning)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

ADD_DEFINITIONS(-std=c++0x)
find_package(Boost REQUIRED)
find_package(SFML REQUIRED COMPONENTS System Window Graphics Audio)

INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR} ${BOOST_INCLUDE_DIR})
add_executable(lightning FXSprite.cpp Bullet.cpp Chaser.cpp Obstacle.cpp Enemy.cpp main.cpp Player.cpp)
target_link_libraries(lightning ${SFML_SYSTEM_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_GRAPHICS_LIBRARY} ${SFML_AUDIO_LIBRARY})