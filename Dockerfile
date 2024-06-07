# Use the base Arch Linux image
FROM archlinux:latest

# Update package lists and install necessary tools
RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm cmake gcc make

# Install SDL2 development package
RUN pacman -S --noconfirm sdl2

# Set the working directory in the container
WORKDIR /recreation-of-doom

# Copy the CMakeLists.txt file and other necessary files
COPY CMakeLists.txt .
COPY src/ ./src/

# Create a build directory
RUN mkdir build

# Set the working directory to the build directory
WORKDIR /recreation-of-doom/build

# Run CMake to configure the project
RUN cmake ..

# Build the application using make
RUN make

# Specify the command to run your application
CMD ["./doom"]