cmake_minimum_required(VERSION 3.10)

project(GeometryVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")

set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(src_path "${${PROJECT_NAME}_SOURCE_DIR}/src")
set(header ${header_path}/classes.h)
set(src ${src_path}/classes.cpp)
set(visual_header ${header_path}/drawing_tool.h)
set(visual_src ${src_path}/drawing_tool.cpp)



add_library(${PROJECT_NAME} SHARED ${header} ${src})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${header_path})

add_library(Visualizer SHARED ${visual_header} ${visual_src})
target_include_directories(Visualizer PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${header_path})

add_executable(test1 ${src_path}/test.cpp)
target_compile_options(test1 PUBLIC -lsfml-graphics -lsfml-window -lsfml-system)

target_link_libraries(test1 ${PROJECT_NAME} Visualizer)