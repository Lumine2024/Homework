project(level1)

add_executable(p01_running_letter p01_running_letter/main.c)

add_executable(p02_is_prime p02_is_prime/main.c)

add_executable(p03_all_primes p03_all_primes/main.c)

add_executable(p04_goldbach p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.c)

add_executable(p06_hanoi p06_hanoi/main.c)

add_executable(p07_maze p07_maze/main.c)
# 由于使用了EasyX，搭载的是WinMain作为主函数（而不是main），故project8 push_boxes无法在cmake中启动
# add_executable(p08_push_boxes 
#    p08_push_boxes/main.cpp
#    p08_push_boxes/Graphic_Logic.cpp
#    p08_push_boxes/Graphic_Logic.h
#    p08_push_boxes/Game_Logic.cpp
#    p08_push_boxes/Game_Logic.h
#    p08_push_boxes/Common.hpp
# )

add_executable(p09_linked_list p09_linked_list/main.c)

add_executable(p10_warehouse p10_warehouse/main.cpp)

add_executable(Ex1_Queue Ex1_Queue/main.c)
