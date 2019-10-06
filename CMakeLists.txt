cmake_minimum_required(VERSION 3.13)
project(MapGeneration C)

set(CMAKE_C_STANDARD 11)

add_executable(MapGeneration Sources/main.c Header/room.h Header/shape.h Sources/Path/contourn.c Header/contourn.h Sources/init_var.c Sources/perlin_noise.c)

target_link_libraries(MapGeneration ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/PDCurses/wincon/pdcurses.a)

if (UNIX)
	target_link_libraries(MapGeneration m)
	target_link_libraries(MapGeneration ncurses)
	target_compile_options(MapGeneration PRIVATE -Wall -Wextra -g -O0)
endif (UNIX)