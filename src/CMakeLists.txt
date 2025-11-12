file(GLOB_RECURSE LIB_SRCS
    geometry2d.cpp
    vector2d.cpp
)

add_library(${THE_LIB} STATIC ${LIB_SRCS})
target_include_directories(${THE_LIB} PUBLIC include)

add_executable(${THE_APP} main.cpp)
target_link_libraries (${THE_APP} PRIVATE ${THE_LIB})