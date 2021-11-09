cmake_minimum_required(VERSION 3.10)

project(GeometryVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -g")

set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(src_path "${${PROJECT_NAME}_SOURCE_DIR}/src")
set(header ${header_path}/classes.h)
set(src ${src_path}/classes.cpp)


add_library(${PROJECT_NAME} SHARED ${header} ${src})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${header_path})
target_link_options(${PROJECT_NAME} PUBLIC -lsfml-graphics -lsfml-window -lsfml-system)
target_compile_options(${PROJECT_NAME} PUBLIC -lsfml-graphics -lsfml-window -lsfml-system)

add_executable(main ${src_path}/window.cpp)
target_link_options(main PUBLIC -lsfml-graphics -lsfml-window -lsfml-system)
target_compile_options(main PUBLIC -lsfml-graphics -lsfml-window -lsfml-system)

target_link_libraries(main ${PROJECT_NAME})