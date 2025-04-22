cmake_minimum_required(VERSION 3.24)
project(StraightWeather)

set(CMAKE_CXX_STANDARD 17)

add_executable(StraightWeather
    main.cpp
    CSVLoader.cpp
    hashmap.cpp
    heap.cpp
    CSVLoader.h
    hashmap.h
    heap.h
)
