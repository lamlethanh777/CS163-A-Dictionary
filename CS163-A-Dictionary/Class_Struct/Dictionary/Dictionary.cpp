#include "Dictionary.h"

// Helper
std::string savePath(const std::string datasetName, const std::string fileName) {
    return "Data/Dict_" + datasetName + "/" + fileName;
}

// Constructor ~ changeDataset()
Dictionary::Dictionary(const std::string newDatasetName) {
    changeDataset(newDatasetName);
}

// Destructor ~ deleteDataset()
Dictionary::~Dictionary() {
    deleteDataset();
}

void Dictionary::serialize() {
    wordsList->serialize(savePath(datasetName, "Trie.txt"));
    definitionsList->serialize(savePath(datasetName, "HashMap.txt"));
    saveVector(searchHistory, savePath(datasetName, "History.txt"));
    saveVector(favoriteList, savePath(datasetName, "Favorite.txt"));
}

// Not really need
/*void Dictionary::deserialize() {
    (*wordsList).deserialize(savePath(datasetName, "Trie.txt"));
    (*definitionsList).deserialize(savePath(datasetName, "HashMap.txt"));
    loadVector(searchHistory, savePath(datasetName, "History.txt"));
    loadVector(favoriteList, savePath(datasetName, "Favorite.txt"));
}*/

// Prepare to change dataset/leave the program
void Dictionary::deleteDataset() {
    // delete and automatically destroy/serialize information
    delete wordsList;
    delete definitionsList;
}

void Dictionary::changeDataset(const std::string newDatasetName) {
    if (datasetName.compare(newDatasetName) == 0) {
        return;
    }

    if (datasetName.compare("") != 0) {
        serialize();
        deleteDataset();
    }

    datasetName = newDatasetName;

    wordsList = new Trie(savePath(datasetName, "Trie.txt"));
    definitionsList = new BinarySearchTree(savePath(datasetName, "HashMap.txt"));
    loadVector(searchHistory, savePath(datasetName, "History.txt"));
    loadVector(favoriteList, savePath(datasetName, "Favorite.txt"));
}
