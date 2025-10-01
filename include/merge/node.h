#ifndef MERGE_DATA_H
#define MERGE_DATA_H
#include <stdexcept>
#include <string>

struct Node {
    int key;
    std::string value;

    Node(const int key, const std::string value) {
        this->key = key;
        if (value.length() > 20) {
            throw std::invalid_argument("value too long");
        }
        this->value = value;
    }
};

#endif