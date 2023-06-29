#include <iostream>
#include "Class/HashMap/HashMap.h"
#include "Class/Trie/Trie.h"

// Testing
int main() {
    string temp = "Data//Dict_Eng-Vie//HashMap.txt";
    BinarySearchTree hashMap(temp);
    hashMap.buildOriginal();

    Quiz testQuiz = hashMap.chooseRightWord();
    cout << "Question: " << testQuiz.question << endl;
    cout << "Choices:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << testQuiz.choices[i] << endl;
    }

    cout << "Answer: " << testQuiz.answer << endl;
	return 0;  
	try {
		// Trie myTrie("Data/Dict_Vie-Eng/Trie.txt") 
		// automatic deserialization

		Trie myTrie;
		// Empty trie
		myTrie.buildTrieFromOriginalSource("Data/Dict_Vie-Eng/Original.txt");
		// Trie built directly from the source file

		std::string tmp;
		std::cout << "Search: ";
		getline(std::cin, tmp);
		while (tmp != "0") {
			std::cout << '\n' << myTrie.searchWord(tmp) ? 1 : 0 << '\n';
			std::cout << "Search: ";
			getline(std::cin, tmp);
		}
		std::cout << "Delete: ";
		getline(std::cin, tmp);
		std::cout << myTrie.deleteWord(tmp) ? 1 : 0 << '\n';
		while (tmp != "0") {
			std::cout << "Delete: ";
			getline(std::cin, tmp);
			std::cout << myTrie.deleteWord(tmp) ? 1 : 0 << '\n';
		}
		myTrie.serialize();
	}
	catch (...) {
		std::cout << "Exception!";
	}
	return 0;
}
