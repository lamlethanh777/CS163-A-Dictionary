#include "AddNewWord.h"

bool addNewWord(Trie& trie, BinarySearchTree& wordMap) {
    std::string word;

    //Input word
    std::cout << "Please enter the word you want to add: ";
    getline(std::cin, word);

    // Check for invalid characters in the word
    if (word.find('`') != std::string::npos || word.find('#') != std::string::npos) {
        std::cout << "Invalid word. Word cannot contain '`' or '#'.\n";
        return false;
    }

    //std::cout << "Enter the definitions: \n";
    //std::string definition;
    //while (getline(std::cin, definition)) {
    //    if (definition.empty())
    //        break;

    //    // Check for invalid characters in the definition
    //    if (definition.find('`') != std::string::npos || definition.find('#') != std::string::npos) {
    //        std::cout << "Invalid definition. Definitions cannot contain '`' or '#'.\n";
    //        return false;
    //    }

    //    definitions.push_back(definition);
    //}

    std::cout << "Enter the definition: \n";
    std::string definition;
    getline(std::cin, definition);

    // Check for invalid characters in the definition
    if (definition.find('`') != std::string::npos || definition.find('#') != std::string::npos) {
        std::cout << "Invalid definition. Definitions cannot contain '`' or '#'.\n";
        return false;
    }

    // Insert in Trie
    if (!trie.insertWord(word)) {
        std::cout << "Failed to insert the word in the dictionary.\n";
        return false;
    }

    // Insert in BSTMap
    TreeNode* currentWord = wordMap.insertWord(word);
    if (!currentWord) {
        std::cout << "Failed to insert the definition in the dictionary.\n";
        // Rollback the insertion in Trie
        trie.removeWord(word);
        return false;
    }
    currentWord->data.definitions.push_back(definition);

    std::cout << "Word and definition added successfully!\n";
    return true;
}
