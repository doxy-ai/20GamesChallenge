add_executable(fish fish.cpp)
target_link_libraries(fish PUBLIC stylizer stylizer::debug stylizer::sdl3)