#ifndef MERGE_DATA_H
#define MERGE_DATA_H
#include <cstring>
#include <stdexcept>

struct Node {
    int key;
    char value[21];

    Node(const int key, const std::string value) {
        this->key = key;
        if (value.length() > 20) {
            throw std::invalid_argument("value too long");
        }
        std::strncpy(this->value, value.c_str(), value.size());
        this->value[value.length()] = '\0';
    }
};

#endif