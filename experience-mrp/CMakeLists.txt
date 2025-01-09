cmake_minimum_required(VERSION 3.28)
project(experience-mrp C)

set(CMAKE_C_STANDARD 11)

set(HEADERS
    mrp.h
    random_walk.h
    td0.h
    mc.h
)

set(SOURCES
    main.c
    random_walk.c
    td0.c
    mc.c
)

add_executable(mrp ${SOURCES} ${HEADERS})
target_link_libraries(mrp m)
