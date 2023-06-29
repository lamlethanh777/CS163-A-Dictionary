#include "Trie.h"

#include <fstream>
#include <iostream>

#include "..\..\Functions\Utilities\OpenFile\OpenFile.h"

TrieNode::TrieNode() {
	isEndOfWord = false;
	for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
		next[i] = nullptr;
	}
}

Trie::Trie() {
	root = new TrieNode();
}

Trie::Trie(const std::string& trieFilePath) {
	root = new TrieNode();
	sourceFilePath = trieFilePath;
	deserialize();
}

void Trie::insertWord(const std::string& word) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		int edge = word[i] - ' ';
		if (!current->next[edge]) {
			current->next[edge] = new TrieNode();
		}
		current = current->next[edge];
	}
	current->isEndOfWord = true;
}

bool Trie::searchWord(const std::string& word) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		int edge = word[i] - ' ';
		if (!current->next[edge]) {
			return false;
		}
		current = current->next[edge];
	}
	return current->isEndOfWord;
}

bool isEmptyTrie(TrieNode* root) {
	for (int i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			return false;
		}
	}
	return true;
}

TrieNode* deleteWordInTrie(TrieNode* root, const std::string& word, int& depth) {
	if (!root) {
		return nullptr;
	}

	if (depth == word.size()) {
		root->isEndOfWord = false;
		if (isEmptyTrie(root)) {
			delete root;
			root = nullptr;
		}
		return root;
	}

	int edge = word[depth] - ' ';
	root->next[edge] = deleteWordInTrie(root->next[edge], word, ++depth);
	--depth;

	if (isEmptyTrie(root) && !root->isEndOfWord) {
		delete root;
		root = nullptr;
	}

	return root;
}

bool Trie::deleteWord(const std::string& word) {
	if (!searchWord(word)) return false;
	int depth = 0;
	deleteWordInTrie(root, word, depth);
	return true;
}

void displayHelper(TrieNode* root, char* wordContainer, int& characterPosition) {
	if (!root) {
		return;
	}

	if (root->isEndOfWord) {
		std::cout << wordContainer << '\n';
	}

	for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			wordContainer[characterPosition++] = i + ' ';
			displayHelper(root->next[i], wordContainer, characterPosition);
			wordContainer[--characterPosition] = '\0';
		}
	}
}

void Trie::displayTrie() {
	char* wordContainer = new char[100]();
	int characterPosition = 0;
	displayHelper(root, wordContainer, characterPosition);
}

void serializeHelper(std::ofstream& fout, TrieNode* root, char* wordContainer, int& characterPosition) {
	if (!root) {
		return;
	}

	if (root->isEndOfWord) {
		fout << wordContainer << '\n';
	}

	for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			wordContainer[characterPosition++] = i + ' ';
			serializeHelper(fout, root->next[i], wordContainer, characterPosition);
			wordContainer[--characterPosition] = '\0';
		}
	}
}

void Trie::serialize() {
	char* wordContainer = new char[100]();
	int characterPosition = 0;

	std::ofstream fout;
	writeFile(fout, sourceFilePath);
	serializeHelper(fout, root, wordContainer, characterPosition);
	fout.close();
}

void Trie::deserialize() {
	std::string word;
	std::ifstream fin;
	readFile(fin, sourceFilePath);
	while (fin.good()) {
		getline(fin, word);
		insertWord(word);
	}
	fin.close();
}

void Trie::buildTrieFromOriginalSource(const std::string& originalFilePath) {
	std::string word, _;

	if (sourceFilePath == "") {
		sourceFilePath = getFolderPath(originalFilePath) + "Trie.txt";
	}

	std::ifstream fin;
	readFile(fin, originalFilePath);
	std::ofstream fout;
	writeFile(fout, sourceFilePath);
	std::cout << sourceFilePath << ' ';

	while (fin.good()) {
		getline(fin, word, '#');
		fout << word << '\n';
		insertWord(word);
		getline(fin, _);
	}

	fin.close();
	fout.close();
}

void deleteTrie(TrieNode* root) {
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
	deleteTrie(root);
	// std::cout << "Trie deleted!";
}
