#ifndef MERGE_FILE_BUFFER_H
#define MERGE_FILE_BUFFER_H
#include <fstream>
#include <vector>

#include "node.h"
#define BUFFER_SIZE 1000000


class ReadFileBuffer {
 private:
 int count = 0;
 std::vector<Node> nodesBuffer;
 std::ifstream in;
 std::size_t nodesInBuffer = 0;

public:
 std::size_t numNodes = 0;
 ReadFileBuffer(const std::string& filename);
 ~ReadFileBuffer();
 Node get();
};


#endif