# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Name of the project
project(BlazeEncryptions)

# Add all the source files needed to build the executable
add_executable(BlazeEncryptions "src/main.cpp" "src/encrypt.cpp" "src/decrypt.cpp" "src/split.cpp")