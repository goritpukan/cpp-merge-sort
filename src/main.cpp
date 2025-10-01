#include <fstream>
#include <iostream>
#include <vector>

#include "../include/merge/data_storage.h"
#include "../include/merge/node.h"

int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

std::string getRandomString(const int length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    result.reserve(length);

    for (int i = 0; i < length; i++) {
        result += chars[rand() % chars.size()];
    }
    return result;
}
void generateRandomFile(const std::string filename, const int size) {
    std::vector<Node> nodes;
    for (int i = 0; i < size; i++) {
        nodes.emplace_back(getRandomNumber(0, 100000), getRandomString(getRandomNumber(0, 20)));
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out) return;
    size_t nodesSize = nodes.size();

    out.write(reinterpret_cast<const char*>(&nodesSize), sizeof(nodesSize));
    for (const auto& node : nodes) {
        out.write(reinterpret_cast<const char*>(&node.key), sizeof(node.key));

        size_t len = node.value.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(node.value.data(), len);
    }
    out.close();
}
int main() {
    srand(time(0));
    DataStorage ds("file.bin");
    generateRandomFile("file.bin", 100); //50000000 +- = 1gb
    return 0;
}
