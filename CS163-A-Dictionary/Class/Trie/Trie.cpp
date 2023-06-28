#include "Trie.h"

#include <fstream>

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

TrieNode* Trie::searchWord(const std::string& word) {
	TrieNode* current = root;
	for (int i = 0; i < word.size(); ++i) {
		int edge = word[i] - ' ';
		if (!current->next[edge]) {
			return nullptr;
		}
		current = current->next[edge];
	}
	return current->isEndOfWord ? current : nullptr;
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
	++depth;
	root->next[edge] = deleteWordInTrie(root->next[edge], word, depth);
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

void serializeHelper(std::ofstream& fout, TrieNode* root, char* wordContainer, int& characterPosition) {
	if (!root) {
		return;
	}

	if (root->isEndOfWord) {
		fout << wordContainer << '\n';
	}

	for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
		if (root->next[i]) {
			wordContainer[characterPosition++] = i;
			serializeHelper(fout, root->next[i], wordContainer, characterPosition);
			wordContainer[--characterPosition] = '\0';
		}
	}
}

void Trie::serialize(const std::string& filePath) {
	char* wordContainer = new char[100]();
	int characterPosition = 0;

	std::ofstream fout;
	writeFile(fout, filePath);
	serializeHelper(fout, root, wordContainer, characterPosition);
}

void Trie::deserialize(const std::string& filePath) {
	std::string word;
	std::ifstream fin;
	readFile(fin, filePath);
	while (fin.good()) {
		getline(fin, word);
		insertWord(word);
	}
}
