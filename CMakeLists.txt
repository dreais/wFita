cmake_minimum_required(VERSION 3.14)
project(MapGeneration C)

set(CMAKE_C_STANDARD 11)

add_executable(MapGeneration Sources/main.c Header/room.h Header/shape.h Sources/shape.c)

target_link_libraries(MapGeneration m)

if (UNIX)
	target_compile_options(MapGeneration PRIVATE -Wall -Wextra)
endif (UNIX)