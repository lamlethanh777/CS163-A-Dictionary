#include "DeleteWord.h"

bool deleteWord(Trie& trie, BinarySearchTree& wordMap) {
    std::string word;
    std::cout << "Enter the word to remove: ";
    std::getline(std::cin, word);

    // Try to remove the word from the trie
    if (!trie.removeWord(word)) {
        std::cout << "Word not found in the dictionary.\n";
        return false;
    }

    // Remove the word from the wordMap
    if (wordMap.removeWord(word)) {
        std::cout << "Word removed successfully from the dictionary.\n";
        return true;
    }
    else {
        std::cout << "Error: Word not found in the dictionary.\n";
        return false;
    }
}
