project(A3)
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.6)

#Header Files
include_directories(include)
include_directories(catch)

#Executables
add_executable(experiment experiment/main.cpp src/Stack.cpp src/GameBoard.cpp test/testCardStack.cpp)
add_executable(test test/testmain.cpp test/testGameBoard.cpp test/testCardStack.cpp src/Stack.cpp src/GameBoard.cpp test/testGameBoard.cpp)