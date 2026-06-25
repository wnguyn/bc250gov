cmake_minimum_required(VERSION 3.16)
project(bc250gov CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bc250gov
    main.cpp
    src/main.cpp
    src/idle/loop.hpp
    src/idle/policy.hpp
    src/idle/sensor.hpp
    src/idle/state.hpp
    src/smu/cmd.hpp
    src/smu/codec.hpp
    src/smu/smu.hpp
    src/smu/transport.hpp
)

target_include_directories(bc250gov PRIVATE src)
