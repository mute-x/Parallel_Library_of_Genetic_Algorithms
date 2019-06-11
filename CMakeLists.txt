cmake_minimum_required(VERSION 2.8)

project(Parallel_Library_of_Genetic_Algorithms)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(TBB REQUIRED)

include_directories( ${TBB_INCLUDE_DIR} )
set(SOURCE_FILES main.cpp genetic.cpp selector.cpp recombinator.cpp mutator.cpp finisher.cpp generator.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(VISUALIZATION visualization/visualization.cpp)
target_link_libraries(${PROJECT_NAME} tbb)

