cmake_minimum_required(VERSION 3.30)
project(20GamesChallenge CXX)

set(CMAKE_CXX_STANDARD 26)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	add_compile_options(-stdlib=libc++)
	add_link_options(-stdlib=libc++)
endif()

add_subdirectory(stylizer)

add_subdirectory(0-HelloGUI)