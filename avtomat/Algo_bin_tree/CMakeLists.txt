cmake_minimum_required(VERSION 3.10)
project(GraphMatrix)

# Явно указываем, что это C (не C++)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Основные флаги компиляции (с предупреждениями)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(PIZDA
    main.c
    Algorithms.c
    stack.c
    deque.c
    adjacency_list.c
    vector.c
    avl_tree.c
)

# Отдельно собираем тесты (если нужно)
add_executable(main 
    ${PIZDA}
)