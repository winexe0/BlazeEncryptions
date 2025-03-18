# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.15)

# Name of the project
project(BlazeEncryptions)

set(CMAKE_CXX_STANDARD 17)
# Add all the source files needed to build the executable
add_executable(BlazeEncryptions "src/main.cpp" "src/old/encrypt.cpp" "src/old/decrypt.cpp" "src/split.cpp" "src/old/old.cpp" "src/old/old.h" "src/new/keygen.cpp" "src/new/keygen.h"   "src/new/encrypt.cpp" "src/new/encrypt.h" "src/new/new.cpp" "src/new/new.h" "src/new/decrypt.cpp" "src/new/decrypt.h" "src/new/keyinfo.cpp" "src/new/keyinfo.h" "src/new/fileSize.cpp" "src/new/fileSize.h")
if(WIN32)
    target_link_libraries(BlazeEncryptions bcrypt.lib)
endif()