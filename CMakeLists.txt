cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME simpletron)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    # Visual Studio (Windows)
    add_compile_options(
        /W4          # Baseline reasonable warnings
        /permissive- # Standards conformance
    )
else()
    # GCC and Clang (Linux/macOS)
    add_compile_options(
        -Wall      # "All" standard warnings
        -Wextra    # Extra warnings not covered by -Wall
        -Wpedantic # Warn if non-standard C++ is used
        -Werror
    )

    if(APPLE)
        add_compile_options(-Wno-error=character-conversion)
    endif()
endif()

set(THE_LIB "simpletron")
set(THE_APP ${THE_LIB}-app)
set(THE_TST ${THE_LIB}-tst)

add_subdirectory(src)
add_subdirectory(test)
