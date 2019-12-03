file(GLOB gui_SRC *.cpp)

add_library(gui ${gui_SRC})

target_include_directories(gui 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${scripting_dir}
        ${resources_dir}
        ${input_dir}
        ${events_dir}
        ${sfml_dir}
        ${ecs_dir}
)