project(lightning)
cmake_minimum_required(VERSION 2.6)

ADD_DEFINITIONS(-std=c++0x)
add_executable(lightning Bullet.cpp Chaser.cpp Obstacle.cpp Enemy.cpp main.cpp Player.cpp)
target_link_libraries(lightning sfml-graphics sfml-audio sfml-window sfml-system)