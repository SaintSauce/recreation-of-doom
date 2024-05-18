cmake_minimum_required(VERSION 3.10)
project(GLFWExampleC)

# Find the GLFW library
find_package(glfw3 REQUIRED)

# Find the OpenGL library
find_package(OpenGL REQUIRED)

# Specify C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable
add_executable(GLFWExampleC main.c)

# Link GLFW and OpenGL with your application
target_link_libraries(GLFWExampleC glfw ${OPENGL_gl_LIBRARY})

