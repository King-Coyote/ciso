file(GLOB SRC *.cpp)

add_library(resources ${SRC})

target_include_directories(resources 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${sfml_dir}
)