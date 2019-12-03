add_library(scripting Scripting.cpp)

target_include_directories(scripting 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${events_dir}
        ${ecs_dir}
)