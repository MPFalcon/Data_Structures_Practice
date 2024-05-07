cmake_minimum_required(VERSION 3.16)

project(
    DataStructuresPractice
    LANGUAGES "C"
    DESCRIPTION "Git Gud With Data Structures"
)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/Graphs/Adjacency_List/CMakeLists.txt")
    add_subdirectory(Graphs/Adjacency_List)
endif()