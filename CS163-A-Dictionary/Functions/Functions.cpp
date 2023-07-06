#include "Functions.h"
#include "../Class_Struct/Trie/Trie.h"
#include "../Class_Struct/HashMap/HashMap.h"
#include <vector>
#include <string>
#include <iostream>

// All features will be assembled at this file as a menu
bool AddNewWord(Trie& trie) {
    std::string word;
    std::vector<std::string> definitions;

    //Input validation
    std::cout << "Enter the word: ";
    getline(std::cin, word);

    // Check for invalid characters in the word
    if (word.find('`') != std::string::npos || word.find('#') != std::string::npos) {
        std::cout << "Invalid word. Word cannot contain '`' or '#'.\n";
        return false;
    }

    std::cout << "Enter the definitions: \n";
    std::string definition;
    while (getline(std::cin, definition)) {
        if (definition.empty())
            break;

        // Check for invalid characters in the definition
        if (definition.find('`') != std::string::npos || definition.find('#') != std::string::npos) {
            std::cout << "Invalid definition. Definitions cannot contain '`' or '#'.\n";
            return false;
        }

        definitions.push_back(definition);
    }

    // Insert in Trie
    //[waiting for response] the function should return sth to indicate success/failure
    /*TrieNode* trieNode = trie.insertWord(word);
    if (!trieNode) {
        std::cout << "Failed to insert word in the Trie.\n";
        return false;
    }*/

    // Insert in BSTMap
    

    std::cout << "Word and definitions added successfully.\n";
    return true;
}
