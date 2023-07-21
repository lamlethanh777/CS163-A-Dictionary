#include "SearchForDefinition.h"

#include <iostream>

void searchForDefinition(BinarySearchTree& definitionsList) {
    // User's input
    std::string definitionPattern;
    std::cout << "Please type in definition pattern you want to search for: ";
    getline(std::cin, definitionPattern);

    vector<TreeNode*> words = definitionsList.searchForDefinition(definitionPattern);
    if (!words.empty()) {
        std::cout << "Words found! This is the list of words:\n\n";
        for (int i = 0; i < (int)words.size(); ++i) {
            cout << i + 1 << ": " << words[i]->data.word << "\n";
        }

        while (1) {
            int num = 0;
            cout << "Choose word you want to search for (input 0 to break): "; cin >> num;
            if (num == 0) break;

            if (num > (int)words.size() || num < 0) {
                cout << "Invalid input!!\n";
                continue;
            }

            std::cout << "WORD: " << words[num - 1]->data.word << "\nDEFINITIONS:\n";
            for (const auto& it : words[num - 1]->data.definitions) {
                std::cout << "- " << it << '\n';
            }
        }
    }
    else {
        cout << "No words with definition pattern found!! \n";
    }
}
