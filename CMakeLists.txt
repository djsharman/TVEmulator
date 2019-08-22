# Minimum CMake version required to generate
# our build system
cmake_minimum_required(VERSION 3.0)

# Name of our Project
project(MyProject)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# add_executable creates an executable with
# The given name.
add_executable(MyEXE main.cpp tvParams.cpp ledValueSelect.cpp sceneRunner.cpp pwmOutput)

# Make sure the executable links to the wiringPi lib
target_link_libraries(MyEXE wiringPi wiringPiDev Threads::Threads)