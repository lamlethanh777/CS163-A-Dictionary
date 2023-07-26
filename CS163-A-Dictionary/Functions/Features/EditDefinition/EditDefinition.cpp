#include "EditDefinition.h"

void editDefinition(Trie& trie, BinarySearchTree& wordMap) {
    std::string word;
    std::cout << "Enter the word to edit its definition: ";
    std::getline(std::cin, word);

    long long hashIndex = trie.searchWord(word);
    if (hashIndex == -1) {
        std::cout << "Word not found.\n";
        return;
    }

    TreeNode* hashMapNode = wordMap.searchWord(hashIndex);
    if (hashMapNode == nullptr) {
        std::cout << "Error: Word not found in the hash map.\n";
        return;
    }

    std::cout << "Current definitions:\n";
    int i = 0;
    for (const std::string& definition : hashMapNode->data.definitions) {
        ++i;
        std::cout << i << ". " << definition << '\n';
    }

    std::cout << "Select an action:\n";
    std::cout << "1. Add a definition\n";
    std::cout << "2. Remove a definition\n";
    std::cout << "3. Modify a definition\n";
    int action;
    std::cout << "Enter your choice: ";
    std::cin >> action;
    std::cin.ignore();  // Ignore the newline character

    switch (action) {
    case 1: {
        std::string newDefinition;
        std::cout << "Enter the new definition to add: ";
        std::getline(std::cin, newDefinition);
        hashMapNode->data.definitions.push_back(newDefinition);
        std::cout << "Definition added successfully.\n";
        break;
    }

    case 2: {
        int index;
        std::cout << "Enter the index of the definition to remove: ";
        std::cin >> index;
        --index;
        std::cin.ignore();  // Ignore the newline character
        if (index >= 0 && index < hashMapNode->data.definitions.size()) {
            hashMapNode->data.definitions.erase(hashMapNode->data.definitions.begin() + index);
            std::cout << "Definition removed successfully.\n";
        }
        else {
            std::cout << "Invalid index.\n";
        }
        break;
    }

    case 3: {
        int index;
        std::cout << "Enter the index of the definition to modify: ";
        std::cin >> index;
        --index;
        std::cin.ignore();  // Ignore the newline character
        if (index >= 0 && index < hashMapNode->data.definitions.size()) {
            std::string newDefinition;
            std::cout << "Enter the new definition: ";
            std::getline(std::cin, newDefinition);
            hashMapNode->data.definitions[index] = newDefinition;
            std::cout << "Definition modified successfully.\n";
        }
        else {
            std::cout << "Invalid index.\n";
        }
        break;
    }
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

