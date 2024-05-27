cmake_minimum_required(VERSION 3.10)        # Minimum version of CMake required
project(DoomGame)                           # Name of the project

# Specify C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add all source files in src directory
file(GLOB SOURCES "src/*.c")

# Add executable
add_executable(DoomExecutable ${SOURCES})

# Include directories
target_include_directories(DoomExecutable PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Find and link GLFW, OpenGL, GLEW, and GLAD
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Link libraries
target_link_libraries(DoomExecutable PRIVATE glfw GLEW::GLEW)

# Optionally, add the lib directory if you have custom libraries
target_link_directories(DoomExecutable PRIVATE ${PROJECT_SOURCE_DIR}/lib)