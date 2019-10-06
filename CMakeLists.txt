cmake_minimum_required(VERSION 3.13)
project(MapGeneration C)

set(CMAKE_C_STANDARD 11)

add_executable(MapGeneration Sources/main.c Header/room.h Header/shape.h Sources/Path/path.c Header/path.h Sources/init_var.c Sources/perlin_noise.c Header/print.h Sources/Character/movement.c Header/character.h Sources/Character/player.c Sources/Print/print_room.c Sources/Print/print_stats.c Sources/game_loop.c Header/core_game.h Sources/Character/monster.c Sources/Path/free_path.c Sources/Path/search.c)

target_link_libraries(MapGeneration ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/PDCurses/wincon/pdcurses.a)

if (UNIX)
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIRS})
	target_compile_options(MapGeneration PRIVATE -Wall -Wextra -g -O0)
	target_link_libraries(MapGeneration m)
	target_link_libraries(MapGeneration ${CURSES_LIBRARIES})
endif (UNIX)