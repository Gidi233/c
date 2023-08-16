#include "File.hpp"

File::File() {}
File::File(int sendID1, string send_name1, string filename1, size_t size1, string filehash1) : sendID(sendID1), send_name(send_name1), filename(filename1), size(size1), filehash(filehash1) {}

std::string getFileHash(const std::string &filename)
{

    std::ifstream file(filename, std::ios::binary);

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0);

    std::hash<std::string> hasher;
    // hasher.seed(12345);
    // hasher.reserve(0);如果是c11以上的话要加上？？

    std::string content(size, ' ');
    file.read(&content[0], size);

    std::string hash_str = std::to_string(hasher(content));
    return hash_str;
}

void File::toString() const
{
    cout << "文件名:" << filename << "大小:" << size / 1048576 << "MB\n发送用户:" << send_name << "(ID:" << sendID << ")" << endl;
}