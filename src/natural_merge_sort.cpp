#include "../include/merge/natural_merge_sort.h"

#include <fstream>
#include <iostream>
#include <string>
NaturalMergeSort::NaturalMergeSort(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open file");

    Node n(0, "");

    while (in.read(reinterpret_cast<char*>(&n), sizeof(Node))) {
        nodes.push_back(n);
    }
}

void NaturalMergeSort::PrintNodes() {
    for (int i = 0; i < nodes.size(); i++) {
        std::cout << nodes[i].key << ": " << nodes[i].value << std::endl;
    }
}

void NaturalMergeSort::Merge(int left, int mid, int right) {
    std::vector<Node> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (nodes[i].key < nodes[j].key) {
            temp.push_back(nodes[i++]);
        }else {
            temp.push_back(nodes[j++]);
        }
    }

    while (i <= mid) {
        temp.push_back(nodes[i++]);
    }

    while (j <= right) {
        temp.push_back(nodes[j++]);
    }

    for (int k = left; k <= right; k++) {
        nodes[k] = temp[k - left];
    }
}

void NaturalMergeSort::Sort() {
    int n = nodes.size();
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right) {
                Merge(left, mid, right);
            }
        }
    }
}
bool NaturalMergeSort::IsSorted() {
    for (int i = 0; i < nodes.size() - 1; i++) {
        if (nodes[i].key > nodes[i + 1].key) return false;
    }
    return true;
}
