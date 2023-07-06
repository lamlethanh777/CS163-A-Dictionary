#ifndef TRIE_H
#define TRIE_H

#define NUMBER_OF_EDGES 69 // number of usable characters, starts from space (32) to '~' (126)

#include<string>

struct TrieNode {
	long long hashIndex;
	TrieNode* next[NUMBER_OF_EDGES]; 

	TrieNode() {
		hashIndex = -1;
		for (char i = 0; i < NUMBER_OF_EDGES; ++i) {
			next[i] = nullptr;
		}
	}
};

char charToEdge(char character);
char edgeToChar(char edge);

class Trie {
private:
	TrieNode* root;
	std::string sourceFilePath; 
	// Data structure file path - Trie.txt

public:
	/* -------------- TRIE MAIN FUNCTIONS --------------------- */

	Trie();
	// Create empty trie -> NEVER USE

	Trie(const std::string& trieFilePath);
	// Build trie from the Trie.txt file in dictionary folder -> SUGGESTED

	void buildTrieFromOriginalSource(const std::string& originalFilePath);
	// Build trie from the Original.txt file in dictionary folder -> ONLY WHEN RESET

	void serialize();
	// Save trie's information to Trie.txt file -> MUST USE WHEN DELETE TRIE

	void deserialize();
	// Build trie from Trie.txt (already included in the second constructor) -> NOT SUGGESTED

	~Trie();
	// Destructor (automatically destroy the object(trie) when going out of scope) -> NO NEED TO CALL

	/* -------------- CUSTOM FUNCTIONS --------------------- */

	bool insertWord(const std::string& word, long long hashIndex);

	long long searchWord(const std::string& word);
	// Return -1 if no word found, else return a hashIndex that is the index of a node in the balanced BST -> hashIndex is to find that node

	bool removeWord(const std::string& word);

	void displayTrie();
};

#endif // !TRIE_H
