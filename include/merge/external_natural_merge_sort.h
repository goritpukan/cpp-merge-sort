#ifndef MERGE_EXTERNAL_NATURAL_MERGE_SORT_H
#define MERGE_EXTERNAL_NATURAL_MERGE_SORT_H
#include <string>


class ExternalNaturalMergeSort {
private:
    std::string filename;
    void Merge();
public:
    ExternalNaturalMergeSort(std::string filename);
    void Sort();
};


#endif
