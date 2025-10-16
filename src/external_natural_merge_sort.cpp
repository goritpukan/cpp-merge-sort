#include "../include/merge/external_natural_merge_sort.h"

#include <iostream>

#include "../include/merge/read_file_buffer.h"
#include "../include/merge/write_file_buffer.h"

ExternalNaturalMergeSort::ExternalNaturalMergeSort(std::string filename) {
    this->filename = filename;
}

void ExternalNaturalMergeSort::Merge() {
    WriteFileBuffer *output = new WriteFileBuffer(filename);
    ReadFileBuffer B("B");
    ReadFileBuffer C("C");

    Node currBNode, currCNode;
    bool hasB = !B.isEmpty();
    bool hasC = !C.isEmpty();

    if (hasB) currBNode = B.get();
    if (hasC) currCNode = C.get();

    while (hasB || hasC) {
        bool runEndB = false;
        bool runEndC = false;

        while ((!runEndB && hasB) || (!runEndC && hasC)) {
            if (!runEndB && hasB &&
                (!hasC || runEndC || currBNode.key <= currCNode.key)) {
                output->Write(currBNode);

                if (B.isEmpty()) {
                    hasB = false;
                    runEndB = true;
                } else {
                    Node next = B.get();
                    if (next.key < currBNode.key)
                        runEndB = true;
                    currBNode = next;
                }
                } else if (!runEndC && hasC) {
                    output->Write(currCNode);

                    if (C.isEmpty()) {
                        hasC = false;
                        runEndC = true;
                    } else {
                        Node next = C.get();
                        if (next.key < currCNode.key)
                            runEndC = true;
                        currCNode = next;
                    }
                }
        }
    }

    delete output;
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

        Merge();
    }

    std::remove("B");
    std::remove("C");
}
