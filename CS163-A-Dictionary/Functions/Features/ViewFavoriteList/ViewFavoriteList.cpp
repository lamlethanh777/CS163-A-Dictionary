#include"ViewFavoriteList.h"

#include <iostream>

void viewFavoriteList(std::vector<std::string>& favoriteList) {
    if (favoriteList.size() == 0) {
        std::cout << "You haven't add any word to your favorite list.\n";
        return;
    }

    std::cout << "This is the list of your favorite word(s):\n";
    for (int i = favoriteList.size() - 1; i >= 0; i--) {
        std::cout << favoriteList[i] << '\n';
    }
}
