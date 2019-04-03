file(GLOB SRC *.cpp)

add_library(ecs ${SRC})

target_include_directories(ecs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${sfml_dir}
        ${resources_dir}
        ${mun_dir}
)

target_link_libraries(ecs
    luavm
)