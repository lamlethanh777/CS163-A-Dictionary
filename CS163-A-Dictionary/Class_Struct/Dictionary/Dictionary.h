#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../HashMap/HashMap.h"
#include "../Trie/Trie.h"
#include "../../Functions/Utilities/VectorFunctions/VectorFunctions.h"

class Dictionary {
public:
    std::string datasetName;
    Trie* wordsList;
    BinarySearchTree* definitionsList;
    std::vector<std::string> searchHistory;
    std::vector<std::string> favoriteList;

    /* ------------------ DICTIONARY FUNCTIONS --------------------- */
    Dictionary() = default;

    // Constructor ~ changeDataset()
    Dictionary(const std::string newDatasetName);

    // Destructor ~ deleteDataset()
    ~Dictionary();

    // Manually serialize is better
    void serialize();

    // Prepare to change dataset/leave the program
    void deleteDataset();

    // deleteDataset() + move to new dataset
    void changeDataset(const std::string newDatasetName);

    // Reset to original state
    void resetToOriginal();
};

#endif // !DICTIONARY_H
