cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        )
add_library(library ${SOURCE_LIB})
add_library(map STATIC library/LinkedMap/map.c)
add_library(binary STATIC library/binary/binary.c)
add_library(list STATIC library/ListOfChar/list.c)

add_executable(task1.1 homework1/task1.1.c)
add_executable(task1.2 homework1/task1.2.c)
add_executable(task1.3 homework1/task1.3.c)
add_executable(task1.4 homework1/task1.4.c)
add_executable(task1.5 homework1/task1.5.c)
add_executable(task2.1 homework2/task2.1.c)
target_link_libraries(task2.1 map)
add_executable(task2.2 homework2/task2.2.c)
target_link_libraries(task2.2 list)

add_executable(task3.1 homework3/task1.c)
target_link_libraries(task3.1 binary)
add_executable(task3.2 homework3/task3.2.c)

add_executable(task3.3 homework3/task3.3.c)
target_link_libraries(task3.3 binary)

add_executable(test2.2 test2/test2.2.c)
add_executable(retest1.2 retest1/task2.c)

