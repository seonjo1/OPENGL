cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME cmake_project_example)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})
set(SRC src/main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
