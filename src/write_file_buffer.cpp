#include "../include/merge/write_file_buffer.h"

WriteFileBuffer::WriteFileBuffer(std::string filename) {
    nodesBuffer.reserve(BUFFER_SIZE);

    out.open(filename, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

WriteFileBuffer::~WriteFileBuffer() {
    if (!nodesBuffer.empty()) {
        out.write(reinterpret_cast<const char *>(nodesBuffer.data()), nodesBuffer.size() * sizeof(Node));
    }
    if (out.is_open()) out.close();
}

void WriteFileBuffer::Write(const Node &node) {
    nodesBuffer.push_back(node);

    if (nodesBuffer.size() >= BUFFER_SIZE) {
        out.write(reinterpret_cast<const char *>(nodesBuffer.data()), nodesBuffer.size() * sizeof(Node));
        nodesBuffer.clear();
    }
}
