#include "Trie.h"

#include <fstream>
#include <iostream>

#include "..\..\Functions\Utilities\OpenFile\OpenFile.h"
#include "..\HashMod\HashMod.h"

char charToEdge(char character) {
	if (character >= 'A' && character <= 'Z') {
		character += 32; // 'a' - 'A' = 32
	}
	return character <= '@' ? character - ' ' : character - 58;
}

char edgeToChar(char edge) {
	return edge <= 32 ? edge + 32 : edge + 58;
}

// The idea of 2 functions above is to gather and seperate two groups of characters 
// from space ' ' (32) to '@' (64) and from '[' (91) to '~' (126)
// So that they use the least number of pointers

/* -------------- TRIE MAIN FUNCTIONS --------------------- */

// Create empty trie -> should be deserialized immediately from the suitable sourceFilePath
Trie::Trie() {
	root = new TrieNode();
}

// Automatically build trie from the Trie.txt file in dictionary folder, sourceFilePath is set to Trie.txt by default
Trie::Trie(const std::string& trieFilePath) {
	root = new TrieNode();
	sourceFilePath = trieFilePath;
	deserialize();
}

// Manually build trie from the Original.txt file in dictionary folder, sourceFilePath is set to Trie.txt by default
void Trie::buildTrieFromOriginalSource(const std::string& originalFilePath) {
	std::string word;

	if (sourceFilePath == "") {
		sourceFilePath = getFolderPath(originalFilePath) + "Trie.txt";
	}

	std::ifstream fin;
	readFile(fin, originalFilePath);
	std::ofstream fout;
	writeFile(fout, sourceFilePath);

	while (getline(fin, word)) {
		int delimiterPosition = word.find_last_of('`');
		word = word.substr(0, delimiterPosition);
		fout << word << '\n';

		hashMod curHash(word);
		long long hashIndex = curHash.getHash();
		insertWord(word, hashIndex);
	}

	fin.close();
	fout.close();
}

// Helper
void serializeHelper(std::ofstream& fout, TrieNode* root, std::string& wordContainer) {
	if (!root) {
		return;
	}

	if (root->hashIndex != -1) {
		fout << wordContainer << ' ' << root->hashIndex << '\n';
	}

	for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			wordContainer.push_back(edgeToChar(i));
			serializeHelper(fout, root->next[i], wordContainer);
			wordContainer.pop_back();
		}
	}
}

// Manually save trie's information to: 1. Trie.txt (by default) or 2. inputSourcefilePath
void Trie::serialize(const std::string inputedSourceFilePath) {
	std::string wordContainer;

    if (inputedSourceFilePath != "") {
        sourceFilePath = inputedSourceFilePath;
    }

    std::ofstream fout;
	writeFile(fout, sourceFilePath);
	serializeHelper(fout, root, wordContainer);
	fout.close();
}

// Manually build trie from: 1. Trie.txt (by default) or 2. inputSourcefilePath
void Trie::deserialize(const std::string inputedSourceFilePath) {
	std::string word;

    if (inputedSourceFilePath != "") {
        sourceFilePath = inputedSourceFilePath;
    }

    std::ifstream fin;
	readFile(fin, sourceFilePath);
	while (getline(fin, word)) {
		int spacePosition = word.find_last_of(' ');
		long long hashIndex = stoll(word.substr(spacePosition + 1));
		word = word.substr(0, spacePosition);
		insertWord(word, hashIndex);
	}
	fin.close();
}

void deleteTrie(TrieNode*& root) {
	if (!root) {
		return;
	}

	for (int i = 0; i < NUMBER_OF_EDGES; ++i) {
		deleteTrie(root->next[i]);
	}
	delete root;
	root = nullptr;
}

Trie::~Trie() {
	serialize();
	deleteTrie(root);
}

/* -------------- CUSTOM FUNCTIONS --------------------- */

// Return false if allocation failed, true if successfully inserted
bool Trie::insertWord(const std::string& word, long long hashIndex) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		char edge = charToEdge(word[i]);
		if (!current->next[edge]) {
			current->next[edge] = new TrieNode();
            if (!current->next[edge]) {
                // Failed to allocate memory for the new node
                return false;
            }
		}
		current = current->next[edge];
	}

    if (current->hashIndex != -1) {
           return false;
    }
    if (hashIndex == -1) {
        hashMod curHash(word);
        current->hashIndex = curHash.getHash();
    }
    else {
        current->hashIndex = hashIndex;
    }

    return true;  // Insertion is successful
}


// Return -1 if no word found, else return a hashIndex that is the index of a node in the balanced BST -> hashIndex is to find that node
long long Trie::searchWord(const std::string& word) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		char edge = charToEdge(word[i]);
		if (!current->next[edge]) {
			return false;
		}
		current = current->next[edge];
	}
	return current->hashIndex;
}

// Helper
bool isEmptyTrie(TrieNode* root) {
	for (int i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			return false;
		}
	}
	return true;
}

// Helper
TrieNode* removeWordHelper(TrieNode* root, const std::string& word, int depth = 0) {
	if (!root) {
		return nullptr;
	}

	if (depth == word.size()) {
		root->hashIndex = -1;
		if (isEmptyTrie(root)) {
			delete root;
			root = nullptr;
		}
		return root;
	}

	char edge = charToEdge(word[depth]);
	root->next[edge] = removeWordHelper(root->next[edge], word, depth + 1);

	if (isEmptyTrie(root) && root->hashIndex == -1) {
		delete root;
		root = nullptr;
	}

	return root;
}

// Return false if no word found, otherwise remove and return true
bool Trie::removeWord(const std::string& word) {
	if (!searchWord(word)) return false;
	removeWordHelper(root, word);
	return true;
}

// Helper
void displayHelper(TrieNode* root, std::string& wordContainer) {
	if (!root) {
		return;
	}

	if (root->hashIndex != -1) {
		std::cout << wordContainer << '\n';
	}

	for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			wordContainer.push_back(edgeToChar(i));
			displayHelper(root->next[i], wordContainer);
			wordContainer.pop_back();
		}
	}
}

// Display all words in sorted order
void Trie::displayTrie() {
	std::string wordContainer;
	displayHelper(root, wordContainer);
}
