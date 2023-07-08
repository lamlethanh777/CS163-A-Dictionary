#include "SearchWord.h"

#include <iostream>

void searchWord(Trie& wordsList, BinarySearchTree& definitionsList, std::vector<std::string>& searchHistory) {
    // User's input
    std::string word;
    std::cout << "Please type in the word you want to search for: ";
    getline(std::cin, word);

    // Search History
    searchHistory.push_back(word);
    if (searchHistory.size() > 10) {
        searchHistory.erase(searchHistory.begin());
    }

    long long hashIndex = wordsList.searchWord(word);
    if (hashIndex == -1) {
        std::cout << "Word not found! Please try another word or add this word to this dictionary!\n";
        return;
    }

    TreeNode* currentWord = definitionsList.searchWord(hashIndex);
    if (currentWord) {
        std::cout << "Word found! This is the list of definitions:\n\n";
        std::cout << "WORD: " << word << "\nDEFINITIONS:\n";
        for (const auto& it : currentWord->data.definitions) {
            std::cout << "- " << it << '\n';
        }
    }
    else {
        throw std::invalid_argument("Syncing error! Please try again later!\n");
    }
}
