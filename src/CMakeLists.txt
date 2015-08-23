cmake_minimum_required(VERSION 3.2)

project(fractionizer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

set(target frac)
set(src    main.cpp)

add_executable(${target} ${src})
