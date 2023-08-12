#include"AddRemoveFavoriteWord.h"
#include<iostream>

bool compareStrings(const std::string& a, const std::string& b) {
    return a > b;
}

void addFavoriteWord(Trie& wordsList, std::vector<std::string>& favoriteList) {
    std::string word;
    std::cout << "Please type in the word you want to add to your favorite list: ";
    getline(std::cin, word);

    for (int i = 0; i < favoriteList.size(); i++) {
        if (word.compare(favoriteList[i]) == 0) {
            std::cout << "The word : " << word << " is already in your favorite list\n";
            return;
        }
    }
 
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

void add_removeFavoriteWord(std::string& currentDatasetName,Trie& wordsList, std::vector<std::string>& favoriteList) {
    int commandNumber;
    do {
        std::cout << "\nWhat do you want to do?\n"
            << "1. Add new word to your favorite list\n"
            << "2. Remove a word form your favorite list\n";
        std::string buffer;
        std::cout << "Your choice: ";
        getline(std::cin, buffer);

        if (buffer.size() > 1 || buffer[0] < '0' || buffer[0] > '2') {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Invalid option! Please try again!\n\n"
                      << "***** Current dataset: " << currentDatasetName << " dictionary *****\n\n"
                      << "11. Remove/add word from your favorite list\n";
            commandNumber = 0;
            continue;
        }else commandNumber = std::stoi(buffer);

        switch (commandNumber) {
            case 1: {
                addFavoriteWord(wordsList, favoriteList);
                break;
            }
            case 2: {
                removeFavoriteWord(favoriteList);
                break;
            }
        }
    } while (commandNumber == 0);
}
