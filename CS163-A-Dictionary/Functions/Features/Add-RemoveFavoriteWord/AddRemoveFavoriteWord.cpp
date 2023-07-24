#include"AddRemoveFavoriteWord.h"
#include<iostream>

void AddFavoriteWord(Trie& wordsList, std::vector<std::string>& favoriteList) {
    std::string word;
    std::cout << "Please type in the word you want to add to your favorite list: ";
    getline(std::cin, word);

    if (word.find('`') != std::string::npos || word.find('#') != std::string::npos) {
        std::cout << "Invalid word. Word cannot contain '`' or '#'.\n";
        return ;
    }

    long long hashIndex = wordsList.searchWord(word);
    if (hashIndex == -1) {
        std::cout << "Word not found! Please try another word or add this word to this dictionary!\n";
        return;
    }
    else {
        favoriteList.push_back(word);
        std::cout << "The word :" << word << " is added to your favorite list\n";
    }
}

void RemoveFavoriteWord(std::vector<std::string>& favoriteList) {
    std::string word;
    std::cout << "Please type in the word you want to remove form favorite list: ";
    getline(std::cin, word);

    if (word.find('`') != std::string::npos || word.find('#') != std::string::npos) {
        std::cout << "Invalid word. Word cannot contain '`' or '#'.\n";
        return;
    }
        
    for (int i = 0; i < favoriteList.size(); i++) {
        if (word == favoriteList[i]) {
            favoriteList.erase(favoriteList.begin()+i);
            std::cout << "The word : " << word << " is removed form your favorite list\n";
            return;
        }
    }
    std::cout << "Your favorite list doesn't contain the word " << word<<'\n';
}
