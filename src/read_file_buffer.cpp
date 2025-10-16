#include "../include/merge/read_file_buffer.h"

#include <fstream>
#include <iostream>

ReadFileBuffer::ReadFileBuffer(const std::string &filename) {
    nodesBuffer.reserve(BUFFER_SIZE);
    in.open(filename, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    in.seekg(0, std::ios::end);
    std::size_t fileSize = in.tellg();
    in.seekg(0, std::ios::beg);
    numNodes = fileSize / sizeof(Node);
}

ReadFileBuffer::~ReadFileBuffer() {
    if (in.is_open()) in.close();
}

Node ReadFileBuffer::get() {
    if (count >= nodesInBuffer) {
        in.read(reinterpret_cast<char *>(nodesBuffer.data()), BUFFER_SIZE * sizeof(Node));
        nodesInBuffer = in.gcount() / sizeof(Node);
        count = 0;
        if (nodesInBuffer == 0) {
            throw std::out_of_range("No more nodes to read");
        }
    }
    return nodesBuffer[count++];
}

bool ReadFileBuffer::isEmpty() {
    return count >= nodesInBuffer && in.peek() == EOF;
}
