cmake_minimum_required(VERSION 3.30)
project(markov_decision_process C)

set(CMAKE_C_STANDARD 11)

set(HEADERS
    mdp.h
    gamblers_problem.h
    policy_iteration.h
)

set(SOURCES
    main.c
    gamblers_problem.c
    policy_iteration.c
)

add_executable(mdp ${SOURCES} ${HEADERS})
