# BlazeEncryptions
A Program which encrypts or decrypts text files or messages.
# Building
# Linux
# Requirements
* g++
* cmake
# Windows
# Requirements
* C++ Compiler
* [cmake](https://cmake.org/download/) 

installed in your Path Environment Variable. 
Then you can cd to BlazeEncryptions source directory and execute 
   ```
    cmake .
    cmake --build .
   ```
   which should give you a usable binary for your architecture. If you want to build a different architcture for Linux for the aarch64 architecture then you can use 
   ```
    cmake -D CMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ -S . 
    cmake --build .
   ```
   If you want to build a different architecture for Windows, then instead for ARM64, use
   ```
   cmake -A ARM64 -S .
   cmake --build .
   ```
   In all cases this should leave a BlazeEncryptions or BlazeEncryptions.exe ready to use.