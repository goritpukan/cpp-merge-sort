#include "../include/merge/data_storage.h"

#include <string>
#include <utility>

DataStorage::DataStorage(std::string fileName) {
    this->filename = std::move(fileName);
}

