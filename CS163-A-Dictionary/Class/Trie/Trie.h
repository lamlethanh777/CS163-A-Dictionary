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
public:
	Trie();
	~Trie();
	void insertWord(const std::string& word);
	TrieNode* searchWord(const std::string& word);
	bool deleteWord(const std::string& word);
	void serialize(const std::string& filePath);
	void deserialize(const std::string& filePath);
};

#endif // !TRIE_H
