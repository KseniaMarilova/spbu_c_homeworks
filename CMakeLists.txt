cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})

add_executable(task1.1 homework1/task1.1.c)
add_executable(task1.2 homework1/task1.2.c)
add_executable(task1.3 homework1/task1.3.c)
add_executable(task1.4 homework1/task1.4.c)
add_executable(task1.5 homework1/task1.5.c)

add_library(binary STATIC library/binary/binary.c)
add_executable(task3.1 homework3/task1.c)
target_link_libraries(task3.1 binary)
