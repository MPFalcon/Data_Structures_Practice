cmake_minimum_required(VERSION 3.16)

project(adjacency_list)

set(SRC_FILES
    src/main.c
    src/adjacency_list.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ./include
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)