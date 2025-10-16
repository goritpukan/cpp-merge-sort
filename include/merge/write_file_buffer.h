#ifndef MERGE_WRITE_FILE_BUFFER_H
#define MERGE_WRITE_FILE_BUFFER_H
#include <fstream>
#include <iosfwd>
#include <vector>

#include "node.h"

#define BUFFER_SIZE 2000000


class WriteFileBuffer {
private:
    std::vector<Node> nodesBuffer;
    std::ofstream out;

public:
    WriteFileBuffer(std::string filename);
    ~WriteFileBuffer();
    void Write(const Node &node);
};


#endif