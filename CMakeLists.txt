cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Doom)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add all your source files here
file(GLOB SOURCES "src/*.c")

add_executable(doom ${SOURCES})

# Find SDL2
find_package(SDL2 REQUIRED)

# Add the SDL2 include directory
include_directories(${SDL2_INCLUDE_DIRS})

# Link the SDL2 library
target_link_libraries(doom ${SDL2_LIBRARIES} m)