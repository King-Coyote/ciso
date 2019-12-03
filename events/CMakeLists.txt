add_library(events 
    EventHandler.cpp
    EventQueue.cpp
)

target_include_directories(events 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${ecs_dir}
)
