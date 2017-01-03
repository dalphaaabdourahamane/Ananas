cmake_minimum_required(VERSION 3.6)
project(Kakuro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Jeu/Grille.cpp Jeu/Grille.h Jeu/Variable.cpp Jeu/Variable.h Jeu/Sequence.cpp Jeu/Sequence.h)
add_executable(Kakuro ${SOURCE_FILES})