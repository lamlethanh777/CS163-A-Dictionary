#include<iostream>
#include"ViewRandomWord.h"

void viewRandomWord(BinarySearchTree wordMap) { 
    TreeNode* randomWord = wordMap.randomNode();

    std::cout << "You have generated a random word \n";
    std::cout << "Word:\n"<<randomWord->data.word<<'\n';
    std::cout << "Definitions:\n";
    for (int i = 0; i < randomWord->data.definitions.size(); i++) {
        std::cout << randomWord->data.definitions[i] << '\n';
    }
}
