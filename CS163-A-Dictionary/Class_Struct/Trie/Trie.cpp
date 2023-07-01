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

Trie::Trie() {
	root = new TrieNode();
}

Trie::Trie(const std::string& trieFilePath) {
	root = new TrieNode();
	sourceFilePath = trieFilePath;
	deserialize();
}

void Trie::buildTrieFromOriginalSource(const std::string& originalFilePath) {
	std::string word;

	if (sourceFilePath == "") {
		sourceFilePath = getFolderPath(originalFilePath) + "Trie.txt";
	}

	std::ifstream fin;
	readFile(fin, originalFilePath);
	std::ofstream fout;
	writeFile(fout, sourceFilePath);
	//std::cout << sourceFilePath << ' ';

	while (getline(fin, word)) {
		int delimiterPosition = word.find_last_of('`');
		word = word.substr(0, delimiterPosition);
		fout << word << '\n';
		//std::cout << word << '\n';
		hashMod curHash(word);
		insertWord(word, curHash.getHash());
	}

	fin.close();
	fout.close();
}

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

void Trie::serialize() {
	std::string wordContainer;

	std::ofstream fout;
	writeFile(fout, sourceFilePath);
	serializeHelper(fout, root, wordContainer);
	fout.close();
}

void Trie::deserialize() {
	std::string word;

	std::ifstream fin;
	readFile(fin, sourceFilePath);
	while (getline(fin, word)) {
		int spacePosition = word.find_last_of(' ');
		int hashIndex = stoi(word.substr(spacePosition + 1));
		word = word.substr(0, spacePosition);
		insertWord(word, hashIndex);
		std::cout << word << ' ' << hashIndex << '\n';
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
	// std::cout << "Trie deleted!";
}

/* -------------- CUSTOM FUNCTIONS --------------------- */

void Trie::insertWord(const std::string& word, int hashIndex) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		char edge = charToEdge(word[i]);
		if (!current->next[edge]) {
			current->next[edge] = new TrieNode();
		}
		current = current->next[edge];
	}
	current->hashIndex = hashIndex;
}

bool Trie::searchWord(const std::string& word) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		char edge = charToEdge(word[i]);
		if (!current->next[edge]) {
			return false;
		}
		current = current->next[edge];
	}
	return current->hashIndex != -1;
}

bool isEmptyTrie(TrieNode* root) {
	for (int i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			return false;
		}
	}
	return true;
}

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

bool Trie::removeWord(const std::string& word) {
	if (!searchWord(word)) return false;
	removeWordHelper(root, word);
	return true;
}
