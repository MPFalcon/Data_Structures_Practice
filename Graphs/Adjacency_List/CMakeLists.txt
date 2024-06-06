cmake_minimum_required(VERSION 3.16)

project(adjacency_list)

set(SRC_FILES
    src/main.c
    src/adjacency_list.c
    src/cli_handling.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ./include
)

target_link_libraries(
    ${PROJECT_NAME}
    LINK_PUBLIC
    common_shared
    common_static
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)