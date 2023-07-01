#include <iostream>
#include "Class_Struct/Trie/Trie.h"
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
		// Trie myTrie("Data/Dict_Eng-Eng/Trie.txt");
		// automatic deserialization
		
		Trie myTrie;
		// Empty trie
		myTrie.buildTrieFromOriginalSource("Data/Dict_Slang/Original.txt");
		// Trie built directly from the original file

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
		while (tmp != "0") {
			std::cout << myTrie.removeWord(tmp) ? 1 : 0 << '\n';
			std::cout << "Delete: ";
			getline(std::cin, tmp);
		}
		// myTrie.serialize();
		// No need to call the serialize function as it will be called through the destructor when going out of scope
	}
	catch (std::exception& error) {
		std::cout << error.what();
	}
	return 0;
}
