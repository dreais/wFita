cmake_minimum_required(VERSION 3.10)
project(wfita_remaster C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)

include_directories(${CMAKE_SOURCE_DIR}/Include)

if(APPLE)
    link_directories(/usr/local/Cellar/raylib/3.5.0/lib)
endif()

add_executable(wfita_remaster Sources/main.c Sources/Dep/Noise/perlin_noise.c Include/noise.h Include/init.h Sources/init_var.c Include/core_game.h Sources/game_loop.c Sources/Print/print_maps.c Include/print.h Sources/Core/keyboard.c Sources/Print/print_entities.c)

add_custom_command(
        TARGET wfita_remaster PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources/ $<TARGET_FILE_DIR:wfita_remaster>/Resources
)

if (WIN32)
    target_link_libraries(
            wfita_remaster ${CMAKE_SOURCE_DIR}/Libraries/libraylib.a
    )
    target_link_libraries(wfita_remaster winmm.lib)
endif (WIN32)

if(APPLE)
    target_link_libraries(wfita_remaster raylib)
endif()