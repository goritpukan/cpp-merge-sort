#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <sys/resource.h>
#include <vector>

#include "../include/merge/natural_merge_sort.h"
#include "../include/merge/node.h"

int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

std::string getRandomString(const int length) {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 51);

    std::string s;
    s.reserve(length);

    for (size_t i = 0; i < length; i++) {
        int r = dist(rng);
        if (r < 26) {
            s += static_cast<char>('A' + r);
        } else {
            s += static_cast<char>('a' + (r - 26));
        }
    }
    return s;
}
void generateRandomFile(const std::string filename, const int size) {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 100000000);

    std::unordered_set<int> keys;
    std::vector<Node> nodes;
    nodes.reserve(size);

    while (nodes.size() < size) {
        int k = dist(rng);
        if (keys.insert(k).second) {
            nodes.emplace_back(k, getRandomString(20));
        }
    }
    for (int i = 0; i < size; i++) {
        nodes.emplace_back(dist(rng), getRandomString(20));
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open file");

    for (const auto& node : nodes) {
        out.write(reinterpret_cast<const char*>(&node), sizeof(Node));
    }
}
int main() {

    NaturalMergeSort ms("file-1gb.bin");
    ms.Sort();
    //generateRandomFile("file-50.bin", 50); //25000000 +- = 1gb

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    std::cout << "Peak memory: " << usage.ru_maxrss / 1024.0 << " MB\n";
    return 0;
}
