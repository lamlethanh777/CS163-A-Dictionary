#include <iostream>
#include "Class_Struct/Trie/Trie.h"
#include "Class_Struct/HashMap/HashMap.h"
#include "Functions/Functions.h"

// Testing
int main() {
    // <---------------------------------Random function example----------------------------------->

    /*std::string temp = "Data/Dict_Vie-Eng/HashMap.txt";
    BinarySearchTree hashMap(temp);
    hashMap.buildOriginal();

    Quiz testQuiz = hashMap.chooseRightWord();
    std::cout << "Question: " << testQuiz.question << '\n';
    std::cout << "Choices:\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << testQuiz.choices[i] << '\n';
    }

    std::cout << "Answer: " << testQuiz.answer << '\n';*/

    // <------------------------------Random function example--------------------------------------->

    // <-------------------------------------Trie + HashMap--------------------------------------->

	try {
        BinarySearchTree myTree("Data/Dict_Vie-Eng/HashMap.txt");
		Trie myTrie("Data/Dict_Vie-Eng/Trie.txt");
        std::vector<std::string> searchHistory;
		// automatic deserialization
		
		//Trie myTrie;
		// Empty trie
		//myTrie.buildTrieFromOriginalSource("Data/Dict_Eng-Eng/Original.txt");
		// Trie built directly from the original file

		std::string tmp;
		std::cout << "Search: ";
		getline(std::cin, tmp);
		while (tmp != "0") {
            searchHistory.push_back(tmp);
            // hashIndex is long long
            searchWord(myTrie, myTree, searchHistory);
            std::cout << "Stop? (0 to stop)";
            std::cin >> tmp;
            std::cin.ignore(1000, '\n');
		}

        viewSearchHistory(searchHistory);
		// No need to call the serialize function of trie or hashmap as it will be called through the destructor when going out of scope
	}
	catch (std::exception& error) {
		std::cout << error.what();
	}

    // <----------------------------------------------Trie + HashMap------------------------------------------->
	return 0;
}
