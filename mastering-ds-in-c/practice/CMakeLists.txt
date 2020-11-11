cmake_minimum_required(VERSION 3.0)
project(cds_algo)

set(CMAKE_C_STANDARD 99)

include_directories("include")

add_executable(list 
 examples/list.c
 src/list.c
)

add_executable(stack 
 src/list.c
 src/stack.c
 examples/stack.c
)

add_executable(queue
 src/list.c
 src/queue.c
 examples/queue.c
)

add_executable(set
 src/list.c
 src/set.c
 examples/set.c
)

add_executable(chtbl
 src/list.c
 src/chtbl.c
 examples/chtbl.c
)

add_executable(ohtbl
 src/ohtbl.c
 examples/ohtbl.c
)

add_executable(bitree
 src/list.c
 src/traverse.c
 src/bitree.c
 examples/bitree.c
)

add_executable(heap
 src/heap.c
 examples/heap.c
)

