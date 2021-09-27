cmake_minimum_required(VERSION 3.10)

project(Lecture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g")

set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(src_path "${${PROJECT_NAME}_SOURCE_DIR}/src")
set(header ${header_path}/classes.h)

set(src ${src_path}/classes.cpp)

add_library(${PROJECT_NAME} SHARED ${header} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${${PROJECT_NAME}_SOURCE_DIR}/include)

add_executable(Lecture.test ${src_path}/simulation.cpp)

target_link_libraries(Lecture.test ${PROJECT_NAME})