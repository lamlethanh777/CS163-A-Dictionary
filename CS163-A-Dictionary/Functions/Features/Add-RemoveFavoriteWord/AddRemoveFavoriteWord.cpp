#include"AddRemoveFavoriteWord.h"
#include<iostream>

void addFavoriteWord(Trie& wordsList, std::vector<std::string>& favoriteList) {
    std::string word;
    std::cout << "Please type in the word you want to add to your favorite list: ";
    getline(std::cin, word);

 
    long long hashIndex = wordsList.searchWord(word);
    if (hashIndex == -1) {
        std::cout << "Word not found! Please try another word or add this word to this dictionary!\n";
    }
    else {
        favoriteList.push_back(word);
        std::sort(favoriteList.begin(), favoriteList.end());
        std::cout << "The word :" << word << " is added to your favorite list!\n";
    }
}

void removeFavoriteWord(std::vector<std::string>& favoriteList) {
    std::string word;
    std::cout << "Please type in the word you want to remove form favorite list: ";
    getline(std::cin, word);

        
    for (int i = 0; i < favoriteList.size(); i++) {
        if (word.compare(favoriteList[i]) == 0) {
            favoriteList.erase(favoriteList.begin()+i);
            std::cout << "The word : " << word << " is removed form your favorite list!\n";
            return;
        }
    }
    std::cout << "Your favorite list doesn't contain the word :" << word<<'\n';
}
void add_removeFariteWord(Trie& wordsList, std::vector<std::string>& favoriteList) {
    std::cout << "What do you want to do?\n"
        << "1. Add new word to your favorite list\n"
        << "2. Remove word form your favourite list\n";
    int commandNumber;
    std::cin >> commandNumber;
    switch (commandNumber) 
    {
        case 1: {
            addFavoriteWord(wordsList, favoriteList);
        }
        case 2: {
            removeFavoriteWord(favoriteList);
        }
        default: {
            std::cout << "Invalid option! Please try again!\n\n";
            break;
        }
    }
}
