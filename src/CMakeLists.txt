file(GLOB_RECURSE LIB_SRCS 
    operations.cpp
    simpletron.cpp
)

add_library(${THE_LIB} STATIC ${LIB_SRCS})
target_include_directories(${THE_LIB} PUBLIC include)

add_executable(${THE_APP} main.cpp)
target_link_libraries (${THE_APP} PRIVATE ${THE_LIB})