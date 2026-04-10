cmake_minimum_required(VERSION 3.10)
project(GraphMatrix)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCES
    main.c
    Algorithms.c
    steck.c
    queue.c
    tree.c
    avl_tree.c
)

set(test_avl_tree_resources
    test_avl_tree.c
    Algorithms.c
    steck.c
    queue.c
    tree.c
    avl_tree.c
)

# Тестовая программа
add_executable(main ${SOURCES})

add_executable(test ${test_avl_tree_resources})