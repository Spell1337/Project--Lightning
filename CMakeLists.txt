project(lightning)
add_executable(lightning main.cpp Player.cpp)
target_link_libraries(lightning sfml-graphics sfml-audio sfml-window sfml-system)