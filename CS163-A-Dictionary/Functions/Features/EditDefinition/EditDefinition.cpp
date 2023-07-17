#include "EditDefinition.h"

void editDefinition(Trie& trie, BinarySearchTree& wordMap) {
    std::string word;
    std::cout << "Enter the word to edit its definition: ";
    std::getline(std::cin, word);

    TrieNode* trieNode = trie.searchWord(word);
    if (trieNode == nullptr) {
        std::cout << "Word not found.\n";
        return;
    }

    long long hashIndex = trieNode->hashIndex;
    TreeNode* bstNode = wordMap.searchWord(hashIndex);
    if (bstNode == nullptr) {
        std::cout << "Error: Word not found in the hash map.\n";
        return;
    }

    std::cout << "Current definitions:\n";
    for (const std::string& definition : hashMapNode->definitions) {
        std::cout << "- " << definition << '\n';
    }
}
