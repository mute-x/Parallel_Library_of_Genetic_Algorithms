cmake_minimum_required(VERSION 2.8)

project(Parallel_Library_of_Genetic_Algorithms)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(TBB REQUIRED)

include_directories( ${TBB_INCLUDE_DIR} )

set(SOURCE_FILES main.cpp genetic.cpp selector.cpp recombinator.cpp mutator.cpp finisher.cpp generator.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} tbb)


# NEEDED FOR VISUALIZATION. DO NOT DELETE!

#find_package(OpenCV REQUIRED )
#
#set(CMAKE_CXX_STANDARD 11)
#
#set (VIS_DIR visualization)
#include_directories(${VIS_DIR})
#
#set(VISUALIZATION VISUALIZATION)
#add_executable(${VISUALIZATION} ${VIS_DIR}/main.cpp ${VIS_DIR}/visualizator.cpp)
#
#target_link_libraries(${VISUALIZATION} ${OpenCV_LIBS} )
#
#find_package(fmt)
#target_link_libraries(${VISUALIZATION} fmt::fmt)
