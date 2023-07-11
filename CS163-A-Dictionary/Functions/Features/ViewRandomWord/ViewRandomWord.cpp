#include<iostream>
#include"ViewRandomWord.h"

void viewRandomWord(BinarySearchTree& wordMap) { 
    TreeNode* randomWord = wordMap.randomNode();

    std::cout << "\nYou have generated a random word!\n";
    std::cout << "WORD: " << randomWord->data.word << '\n';
    std::cout << "DEFINITIONS:\n";
    for (int i = 0; i < randomWord->data.definitions.size(); i++) {
        std::cout << "- " << randomWord->data.definitions[i] << '\n';
    }
}
