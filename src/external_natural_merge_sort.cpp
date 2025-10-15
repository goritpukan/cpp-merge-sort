#include "../include/merge/external_natural_merge_sort.h"

#include <iostream>

#include "../include/merge/read_file_buffer.h"
#include "../include/merge/write_file_buffer.h"

ExternalNaturalMergeSort::ExternalNaturalMergeSort(std::string filename) {
    this->filename = filename;
}

// void ExternalNaturalMergeSort::Merge() {
//     WriteFileBuffer *input = new WriteFileBuffer(filename);
//     ReadFileBuffer B("B");
//     ReadFileBuffer C("C");
//
//     if (B.isEmpty()) {
//         while (!C.isEmpty()) {
//             input->Write(C.get());
//         }
//         delete input;
//         return;
//     }
//     if (C.isEmpty()) {
//         while (!B.isEmpty()) {
//             input->Write(B.get());
//         }
//         delete input;
//         return;
//     }
//
//     Node prevBNode = B.get();
//     Node prevCNode = C.get();
//
//     while (!B.isEmpty() && !C.isEmpty()) {
//         if (prevBNode.key <= prevCNode.key) {
//             input->Write(prevBNode);
//             prevBNode = B.get();
//         } else {
//             input->Write(prevCNode);
//             prevCNode = C.get();
//         }
//     }
//
//     if (B.isEmpty()) {
//         input->Write(prevCNode);
//         while (!C.isEmpty()) {
//             input->Write(C.get());
//         }
//     } else {
//         input->Write(prevBNode);
//         while (!B.isEmpty()) {
//             input->Write(B.get());
//         }
//     }
//     delete input;
// }


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

        ReadFileBuffer b("B");
        for (int i = 0; i < b.numNodes; i++) {
            std::cout << b.get().key << std::endl;
        }

        ReadFileBuffer c("C");
        for (int i = 0; i < c.numNodes; i++) {
            std::cout << c.get().key << std::endl;
        }
        break;

        // Merge();
    }
}
