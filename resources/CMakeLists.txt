file(GLOB SRC *.cpp)
file(GLOB TESTS tests/*.cpp)

add_library(resources ${SRC})

target_include_directories(resources 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${sfml_dir}
)

add_executable(test ${TESTS})

target_include_directories(test
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${smfl_dir}
        ${catch_dir}
)

target_link_libraries(test
        sfml-graphics
        resources
)