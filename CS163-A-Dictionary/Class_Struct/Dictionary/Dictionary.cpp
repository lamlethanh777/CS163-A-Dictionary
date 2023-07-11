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
    serialize();
    deleteDataset();
}

// Manually serialize is better
void Dictionary::serialize() {
    wordsList->serialize(savePath(datasetName, "Trie.txt"));
    definitionsList->serialize(savePath(datasetName, "HashMap.txt"));
    saveVector(searchHistory, savePath(datasetName, "History.txt"));
    saveVector(favoriteList, savePath(datasetName, "Favorite.txt"));
}

// Prepare to change dataset/leave the program
void Dictionary::deleteDataset() {
    delete wordsList;
    delete definitionsList;
}

// deleteDataset() + move to new dataset
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

// Reset to original state
void Dictionary::resetToOriginal() {
    // Delete everything
    delete wordsList;
    delete definitionsList;
    searchHistory.clear();
    favoriteList.clear();
    
    std::string originalFilePath = savePath(datasetName, "Original.txt");

    // Build everything from original
    wordsList = new Trie();
    wordsList->buildTrieFromOriginalSource(originalFilePath);
    definitionsList = new BinarySearchTree();
    definitionsList->buildOriginal(originalFilePath);
}
