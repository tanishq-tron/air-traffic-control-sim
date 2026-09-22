cmake_minimum_required(VERSION 3.20)
project(AirTrafficControlSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Header include paths
include_directories(include)

# Header files (explicitly listed for CLion indexing)
set(HEADERS
        include/Aircraft.hpp
        include/Runway.hpp
        include/Scheduler.hpp
)

# Source files
set(SOURCES
        src/main.cpp
        src/Aircraft.cpp
        src/Runway.cpp
        src/Scheduler.cpp
)

# Add both sources and headers to the target executable
add_executable(atc_sim ${SOURCES} ${HEADERS})