#include <iostream>
#include <fstream>
#include <string>
#include "fileSize.h"
using namespace std;
int fourth::fileSize(std::string add) {
    ifstream mySource;
    mySource.open(add, ios_base::binary);
    mySource.seekg(0, ios_base::end);
    int size = mySource.tellg();
    mySource.close();
    return size;
}