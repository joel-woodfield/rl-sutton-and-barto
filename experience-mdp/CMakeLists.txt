cmake_minimum_required(VERSION 3.28)
project(experience-mdp C)

set(CMAKE_C_STANDARD 11)

set(HEADERS
    mdp.h
    sarsa.h
    expected_sarsa.h
    q.h
    cliff_walking.h
)

set(SOURCES
    main.c
    sarsa.c
    expected_sarsa.c
    q.c
    cliff_walking.c
)

add_executable(mdp ${SOURCES} ${HEADERS})
target_link_libraries(mdp m)
