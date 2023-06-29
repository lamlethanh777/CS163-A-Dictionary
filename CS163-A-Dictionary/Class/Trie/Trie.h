#ifndef TRIE_H
#define TRIE_H

#define NUMBER_OF_EDGES 95 // number of usable characters, starts from space (32) to '~' (126)

#include<string>

class TrieNode {
public:
	bool isEndOfWord;
	TrieNode* next[NUMBER_OF_EDGES]; 

	TrieNode();
};

class Trie {
private:
	TrieNode* root;
	std::string sourceFilePath; // Data structure file - Trie.txt

public:
	Trie();
	Trie(const std::string& trieFilePath);
	void insertWord(const std::string& word);
	bool searchWord(const std::string& word);
	bool deleteWord(const std::string& word);
	void displayTrie(); // For testing
	void serialize();
	void deserialize();
	void buildTrieFromOriginalSource(const std::string& originalFilePath); // original.txt
	~Trie();
};

#endif // !TRIE_H
