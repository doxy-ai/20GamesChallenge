add_executable(hellogui hello.cpp)
target_link_libraries(hellogui PUBLIC stylizer stylizer::sdl3 stylizer::imgui)