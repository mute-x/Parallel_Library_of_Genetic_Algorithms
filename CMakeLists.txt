cmake_minimum_required(VERSION 2.8)

project(Parallel_Library_of_Genetic_Algorithms)
add_executable(${PROJECT_NAME} "main.cpp" "genetic.cpp" selector.cpp recombinator.cpp mutator.cpp finisher.cpp generator.cpp)
