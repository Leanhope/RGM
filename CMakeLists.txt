cmake_minimum_required(VERSION 2.8)
project(AlgorithmsDatastructures)
target_link_libraries(
    tiscos_stat
    ${Boost_TIMER_LIBRARY})
set(CMAKE_CXX_FLAGS "-std=gnu++0x")

add_executable(RGM RGM.cpp)
