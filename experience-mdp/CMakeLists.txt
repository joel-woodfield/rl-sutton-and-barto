cmake_minimum_required(VERSION 3.28)
project(experience-mdp C)

set(CMAKE_C_STANDARD 11)

set(HEADERS
    mdp.h
    sarsa.h
    epsilon_greedy.h
    cliff_walking.h
)

set(SOURCES
    main.c
    sarsa.c
    epsilon_greedy.c
    cliff_walking.c
)

add_executable(mdp ${SOURCES} ${HEADERS})
target_link_libraries(mdp m)
