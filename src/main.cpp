#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <sys/resource.h>
#include <vector>

#include "../include/merge/external_natural_merge_sort.h"
#include "../include/merge/natural_merge_sort.h"
#include "../include/merge/node.h"
#include "../include/merge/read_file_buffer.h"
#include "../include/merge/write_file_buffer.h"

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

    // NaturalMergeSort ms("file-1gb.bin");
    // ms.Sort();
    //generateRandomFile("file-25000000.bin", 25000000); //25000000 +- = 1gb

    // WriteFileBuffer* testFile = new WriteFileBuffer("file-10.bin");
    // testFile->Write(Node(3, "a"));
    // testFile->Write(Node(7, "a"));
    // testFile->Write(Node(9, "a"));
    // testFile->Write(Node(4, "a"));
    // testFile->Write(Node(0, "a"));
    // testFile->Write(Node(1, "a"));
    // testFile->Write(Node(5, "a"));
    // testFile->Write(Node(2, "a"));
    // testFile->Write(Node(8, "a"));
    // testFile->Write(Node(6, "a"));
    // delete testFile;

    // ReadFileBuffer* before = new ReadFileBuffer("file-25000000.bin");
    //
    //  std::cout << "After" << std::endl;
    //  size_t count = 0;
    //  bool isSorted = true;
    //  Node prev = before->get();
    //  Node curr;
    //  for (int i = 1; i < before->numNodes; i++) {
    //      count++;
    //      curr = before->get();
    //      if (prev.key > curr.key) {
    //          isSorted = false;
    //          break;
    //      }
    //      prev = curr;
    //  }
    //  std::cout << isSorted << std::endl;
    //  std::cout << before->numNodes << std::endl;
    //  delete before;

    ExternalNaturalMergeSort sort("file-25000000.bin");
    sort.Sort();

    // ReadFileBuffer readFileBuffer("file-25000000.bin");
    //
    //  for (int i = 0; i < readFileBuffer.numNodes; ++i) {
    //      std::cout << readFileBuffer.get().key << std::endl;
    //  }
    //  std::cout << readFileBuffer.numNodes <<std::endl;
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    std::cout << "Peak memory: " << usage.ru_maxrss / 1024.0 << " MB\n";
    return 0;
}
