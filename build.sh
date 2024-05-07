rm -rf ./build

clang-format -i Graphs/Adjacency_List/include/*
clang-format -i Graphs/Adjacency_List/src/*

mkdir build
cd build
cmake ..
make