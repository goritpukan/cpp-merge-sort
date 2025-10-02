
#ifndef MERGE_DATSSTORAGE_H
#define MERGE_DATSSTORAGE_H
#include <string>
#include <vector>

#include "node.h"

class NaturalMergeSort {
private:
    std::vector<Node> nodes;
    void Merge(int left, int mid, int right);
public:
    NaturalMergeSort(const std::string& filename);
    void PrintNodes();
    void Sort();
    bool IsSorted();
};

#endif