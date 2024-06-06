cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyGame VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable
add_executable(my_game src/main.c)

# Specify the path to the SDL2 library and include files
set(SDL2_INCLUDE_DIR "C:/MinGW/include/SDL2")
set(SDL2_LIBRARY_DIR "C:/MinGW/lib")

# Add the SDL2 include directory
include_directories(${SDL2_INCLUDE_DIR})

# Link the SDL2 library
target_link_libraries(my_game mingw32 SDL2main SDL2)