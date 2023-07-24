#ifndef ADD-REMOVE-FAVORITE-WORD
#define ADD-REMOVE-FAVORITE-WORD

#include "../SearchWord/SearchWord.h"
#include "../../Utilities/VectorFunctions/VectorFunctions.h"
#include <string>
#include <vector>

void AddFavoriteWord(Trie& wordsList, std::vector<std::string>& favoriteList);
void RemoveFavoriteWord( std::vector<std::string>& favoriteList);

#endif // !ADD-REMOVE-FAVORITE-WORD
