
#ifndef MERGE_DATSSTORAGE_H
#define MERGE_DATSSTORAGE_H
#include <string>
#include <vector>

#include "node.h"

class DataStorage {
private:
    std::string filename;
public:
    std::vector<Node> nodes;
    DataStorage(std::string fileName);
};

#endif