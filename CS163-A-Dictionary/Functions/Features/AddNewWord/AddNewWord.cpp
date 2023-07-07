#include "AddNewWord.h"

bool addNewWord(Trie& trie, BinarySearchTree& wordMap) {
    std::string word;
    //in case we still want to have several definitions. else, you can just delete this vector
    //std::vector<std::string> definitions;

    //Input validation
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

    std::cout << "Please enter the definitions you want to add (press enter 2 times to stop): \n";
    std::string definition;
    getline(std::cin, definition);
    // Check for invalid characters in the definition
    if (definition.find('`') != std::string::npos || definition.find('#') != std::string::npos) {
        std::cout << "Invalid definition. Definitions cannot contain '`' or '#'.\n";
        return false;
    }
    // Insert in Trie
    if (!trie.insertWord(word)) {
        std::cout << "Failed to insert word in the Trie.\n";
        return false;
    }

    // Insert in BSTMap
    if (!wordMap.insertDefinition(word, definition)) {
        std::cout << "Failed to insert word and definitions in the HashMap.\n";
        // Rollback the insertion in Trie
        trie.removeWord(word);
        return false;
    }

    std::cout << "Word and definitions added successfully.\n";
    return true;
}
