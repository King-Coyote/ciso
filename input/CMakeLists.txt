add_library(input Input.cpp)

target_include_directories(input 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${sfml_dir}
        ${events_dir}
        ${ecs_dir}
)