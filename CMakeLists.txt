cmake_minimum_required (VERSION 3.14.0)
project(ciso)

set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 14)

set(scripting_dir ${CMAKE_CURRENT_SOURCE_DIR}/scripting)
set(events_dir ${CMAKE_CURRENT_SOURCE_DIR}/events)
set(game_dir ${CMAKE_CURRENT_SOURCE_DIR}/game)
set(ecs_dir ${CMAKE_CURRENT_SOURCE_DIR}/game/ECS)
set(gui_dir ${CMAKE_CURRENT_SOURCE_DIR}/gui)
set(input_dir ${CMAKE_CURRENT_SOURCE_DIR}/input)
set(resources_dir ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(scripting_dir ${CMAKE_CURRENT_SOURCE_DIR}/scripting)
set(sfml_dir /usr/include/SFML)
set(mun_dir /usr/include/luavm)
set(thor_dir /usr/include/thor)

add_subdirectory(events)

if(MODULE STREQUAL "game")
    set(TARGET_NAME dummy_main_game)
    add_subdirectory(gui)
    add_subdirectory(scripting)
    add_subdirectory(resources)
    add_subdirectory(input)
    add_subdirectory(game)
    add_executable(${TARGET_NAME} dummy_main_game.cpp)
    target_include_directories(${TARGET_NAME}
        PUBLIC 
            ${events_dir}
            ${scripting_dir}
            ${input_dir}
            ${gui_dir}
            ${resources_dir}
            ${game_dir}
            ${mun_dir}
            ${ecs_dir}
    )
    target_link_libraries(${TARGET_NAME} 
        sfml-graphics 
        sfml-window 
        sfml-system
        lua
        luavm
        events
        scripting
        input
        gui
        resources
        game
    )
elseif(MODULE STREQUAL "events")
    set(TARGET_NAME dummy_main_events)
    add_executable(${TARGET_NAME} dummy_main_events.cpp)
    add_subdirectory(input)
    target_include_directories(${TARGET_NAME}
        PUBLIC 
            ${events_dir}
            ${input_dir}
    )
    target_link_libraries(${TARGET_NAME}
        sfml-graphics 
        sfml-window 
        sfml-system
        lua
        luavm
        events
        input
    )
endif()