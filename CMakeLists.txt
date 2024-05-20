cmake_minimum_required(VERSION 3.10) # Minimum version of CMake required
project(Doom) # Name of your project

# Find the GLFW library
find_package(glfw3 REQUIRED)

# Find the OpenGL library
find_package(OpenGL REQUIRED)

# Specify C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Add the directory where the library file is located
link_directories(lib)

# Add executable
add_executable(DoomExecutable src/glfw_tutorial.c src/glad.c)

# Link GLFW and OpenGL with your application
target_link_libraries(DoomExecutable glfw ${OPENGL_gl_LIBRARY})

