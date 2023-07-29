#ifndef ADD_REMOVE_FAVORITE_WORD
#define ADD_REMOVE_FAVORITE_WORD

#include "../../../Class_Struct/Trie/Trie.h"
#include<vector>
#include <algorithm>

void addFavoriteWord(Trie& wordsList, std::vector<std::string>& favoriteList);
void removeFavoriteWord( std::vector<std::string>& favoriteList);
void add_removeFavoriteWord(std::string& currentDatasetName,Trie& wordsList, std::vector<std::string>& favoriteList);

#endif // !ADD_REMOVE_FAVORITE_WORD
