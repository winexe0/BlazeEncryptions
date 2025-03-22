# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.15)

# Name of the project
project(BlazeEncryptions)

set(CMAKE_CXX_STANDARD 17)

# Add all the source files needed to build the executable
add_executable(BlazeEncryptions 
    "src/main.cpp" 
    "src/1.x/encrypt.cpp" 
    "src/1.x/decrypt.cpp" 
    "src/split.cpp" 
    "src/1.x/old.cpp" 
    "src/1.x/old.h" 
    "src/2.x-3.x/keygen.cpp" 
    "src/2.x-3.x/keygen.h" 
    "src/2.x-3.x/encrypt.cpp" 
    "src/2.x-3.x/encrypt.h" 
    "src/2.x-3.x/new.cpp" 
    "src/2.x-3.x/new.h" 
    "src/2.x-3.x/decrypt.cpp" 
    "src/2.x-3.x/decrypt.h" 
    "src/2.x-3.x/keyinfo.cpp" 
    "src/2.x-3.x/keyinfo.h" 
    "src/2.x-3.x/fileSize.cpp" 
    "src/2.x-3.x/fileSize.h" 
    "src/4.x/encrypt.cpp" 
    "src/4.x/encrypt.h" 
    "src/4.x/decrypt.cpp" 
    "src/4.x/decrypt.h" 
    "src/4.x/keygen.cpp" 
    "src/4.x/keygen.h" 
    "src/4.x/keyinfo.cpp" 
    "src/4.x/keyinfo.h" 
    "src/4.x/new.cpp" 
    "src/4.x/new.h"
    "src/4.x/fileSize.cpp"
    "src/4.x/fileSize.h"
)

# Link bcrypt library on Windows
if(WIN32)
    target_link_libraries(BlazeEncryptions bcrypt.lib)
endif()