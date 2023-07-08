#include "ViewSearchHistory.h"

#include <iostream>

void viewSearchHistory(std::vector<std::string>& searchHistory) {
    if (searchHistory.size() < 1) {
        std::cout << "You haven't searched any word recently! Let's search for some!\n";
        return;
    }

    std::cout << "This is the list of some latest word(s) you searched for:\n";
    for (int i = searchHistory.size() - 1; i >= 0; --i) {
        std::cout << searchHistory[i] << '\n';
    }
}
