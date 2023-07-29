#include"AddRemoveFavoriteWord.h"
#include<iostream>

bool compareStrings(const std::string& a, const std::string& b) {
    return a > b;
}

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
        std::sort(favoriteList.begin(), favoriteList.end(), compareStrings);
        std::cout << "The word :" << word << " is added to your favorite list!\n";
    }
}

void removeFavoriteWord(std::vector<std::string>& favoriteList) {
    std::cout << "Please type in the word you want to remove form favorite list: ";
    std::string word;
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
