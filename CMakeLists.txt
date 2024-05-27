cmake_minimum_required(VERSION 3.10)        # Minimum version of CMake required
project(Doom)                               # Name of the project

# Find the GLFW library
find_package(glfw3 REQUIRED)
if(NOT glfw3_FOUND)
    message(FATAL_ERROR "GLFW3 not found")
endif()

# Find the OpenGL library
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

# Find GLEW
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found")
endif()

# Specify C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directories
target_include_directories(DoomExecutable PUBLIC include)

# Add the directory where the library file is located
set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} lib)

# Add all source files in src directory
file(GLOB SOURCES "src/*.c")

# Add executable
add_executable(DoomExecutable ${SOURCES})

# Link libraries
target_link_libraries(DoomExecutable PRIVATE glfw OpenGL::GL ${GLEW_LIBRARIES})
