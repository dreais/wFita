cmake_minimum_required(VERSION 3.13)
project(wFita C)

set(CMAKE_C_STANDARD 11)

add_executable(wFita Sources/main.c Header/room.h Sources/Path/path.c Header/path.h Sources/init_var.c Sources/perlin_noise.c Header/print.h Sources/Character/movement.c Header/character.h Sources/Character/player.c Sources/Print/print_room.c Sources/Print/print_stats.c Sources/game_loop.c Header/core_game.h Sources/Character/monster.c Sources/Path/free_path.c Sources/Path/search.c Sources/Character/Shared/shared_attack.c Sources/Misc/Weapon/weapon_roll.c Header/item_list.h Sources/Character/Shared/shared_equipment.c Sources/Misc/keyboard.c Sources/Misc/Input/arrows.c Header/Keyboard/input.h Sources/Misc/Input/menu.c Sources/Print/logs.c)

target_link_libraries(wFita ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/PDCurses/wincon/pdcurses.a)

if (UNIX)
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIRS})
	target_compile_options(wFita PRIVATE -Wall -Wextra -g -O0)
	target_link_libraries(wFita m)
	target_link_libraries(wFita ${CURSES_LIBRARIES})
endif (UNIX)