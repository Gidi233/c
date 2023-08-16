#ifndef FILE_
#define FILE_
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <functional>
using std::string, std::cout, std::endl;
// #define _FILE_OFFSET_BITS 64
class File
{
public:
    string send_name, filename, filehash;
    int sendID;
    size_t size; // offset = 0存到数据库//每次直接打开文件信息做检查

    File();
    File(int sendID, string send_name, string filename, size_t size, string filehash);

    void toString() const;
};

std::string getFileHash(const std::string &filename);
#endif