file(GLOB SRC *.cpp)

add_subdirectory(ECS)

add_library(game ${SRC})

target_include_directories(game
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${resources_dir}
        ${gui_dir}
        ${scripting_dir}
        ${events_dir}
        ${mun_dir}
)

target_link_libraries(game
    lua
    luavm
    ecs
)