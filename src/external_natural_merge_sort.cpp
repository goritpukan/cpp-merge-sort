#include "../include/merge/external_natural_merge_sort.h"

#include <iostream>

#include "../include/merge/read_file_buffer.h"
#include "../include/merge/write_file_buffer.h"

ExternalNaturalMergeSort::ExternalNaturalMergeSort(std::string filename) {
    this->filename = filename;
}

void ExternalNaturalMergeSort::Merge() {
    WriteFileBuffer *input = new WriteFileBuffer(filename);
    ReadFileBuffer B("B");
    ReadFileBuffer C("C");

    Node prevBNode, currBNode;
    Node prevCNode, currCNode;
    std::vector<Node> runB;
    std::vector<Node> runC;

    if (!B.isEmpty()) prevBNode = B.get();
    if (!C.isEmpty()) prevCNode = C.get();

    while (!B.isEmpty() || !C.isEmpty()) {
        if (!B.isEmpty()) {
            runB.push_back(prevBNode);
            while (!B.isEmpty()) {
                currBNode = B.get();
                if (currBNode.key < prevBNode.key) break;
                runB.push_back(currBNode);
                prevBNode = currBNode;
            }
        }

        if (!C.isEmpty()) {
            runC.push_back(prevCNode);
            while (!C.isEmpty()) {
                currCNode = C.get();
                if (currCNode.key < prevCNode.key) break;
                runC.push_back(currCNode);
                prevCNode = currCNode;
            }
        }

        size_t i = 0, j = 0;
        while (i < runB.size() && j < runC.size()) {
            if (runB[i].key <= runC[j].key) {
                input->Write(runB[i++]);
            } else {
                input->Write(runC[j++]);
            }
        }

        while (i < runB.size()) {
            input->Write(runB[i++]);
        }

        while (j < runC.size()) {
            input->Write(runC[j++]);
        }

        if (!B.isEmpty()) prevBNode = currBNode;
        if (!C.isEmpty()) prevCNode = currCNode;
        runB.clear();
        runC.clear();
    }

    delete input;
}

void ExternalNaturalMergeSort::Sort() {
    Node currentNode;
    Node prevNode;

    bool isSorted = false;
    bool isFileB = true;

    while (!isSorted) {
        isSorted = true;
        ReadFileBuffer input(filename);
        WriteFileBuffer *B = new WriteFileBuffer("B");
        WriteFileBuffer *C = new WriteFileBuffer("C");

        prevNode = input.get();
        isFileB = true;

        for (int i = 1; i < input.numNodes; i++) {
            currentNode = input.get();
            if (isFileB) {
                B->Write(prevNode);
            } else {
                C->Write(prevNode);
            }
            if (currentNode.key < prevNode.key) {
                isSorted = false;
                isFileB = !isFileB;
            }
            prevNode = currentNode;
        }
        if (isFileB) {
            B->Write(prevNode);
        } else {
            C->Write(prevNode);
        }
        delete B;
        delete C;

        // ReadFileBuffer b("B");
        // for (int i = 0; i < b.numNodes; i++) {
        //     std::cout << b.get().key << std::endl;
        // }
        //
        // ReadFileBuffer c("C");
        // for (int i = 0; i < c.numNodes; i++) {
        //     std::cout << c.get().key << std::endl;
        // }
        // break;

        Merge();
    }

    std::remove("B");
    std::remove("C");
}
