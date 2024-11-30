cmake_minimum_required(VERSION 3.28)
project(multi_armed_bandits C)

set(CMAKE_C_STANDARD 11)

add_executable(epsilon_greedy epsilon_greedy.c)
target_link_libraries(epsilon_greedy m)
