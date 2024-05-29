cmake_minimum_required(VERSION 3.10)
project(DoomGame)

# Specify C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add all source files in src directory
file(GLOB SOURCES "src/*.c")

# Add executable
add_executable(Doom ${SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(Doom OpenGL::GL)

# Include directories
target_include_directories(Doom PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Optionally, add the lib directory if you have custom libraries
target_link_directories(Doom PRIVATE ${PROJECT_SOURCE_DIR}/lib)

# Link against libglut.dylib
find_library(GLUT_LIBRARY NAMES glut PATHS ${PROJECT_SOURCE_DIR}/lib/libglut.dylib)
if(NOT GLUT_LIBRARY)
    message(FATAL_ERROR "libglut.dylib not found")
endif()
target_link_libraries(Doom ${GLUT_LIBRARY})