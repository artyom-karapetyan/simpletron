cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME simpletron)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THE_LIB "simpletron")
set(THE_APP ${THE_LIB}-app)
set(THE_TST ${THE_LIB}-tst)

add_subdirectory(src)
add_subdirectory(test)
