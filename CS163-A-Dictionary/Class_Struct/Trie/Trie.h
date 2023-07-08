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

    // Create empty trie -> should be deserialized immediately from the suitable sourceFilePath 
	Trie();

    // Build trie from the Trie.txt file in dictionary folder, sourceFilePath is set to Trie.txt by default
	Trie(const std::string trieFilePath);

    // Build trie from the Original.txt file in dictionary folder, sourceFilePath is set to Trie.txt by default
	void buildTrieFromOriginalSource(const std::string originalFilePath);

    // Manually save trie's information to: 1. Trie.txt (by default) or 2. inputSourcefilePath
	void serialize(const std::string inputedSourceFilePath = "");

    // Manually build trie from: 1. Trie.txt (by default) or 2. inputSourcefilePath
	void deserialize(const std::string inputedSourceFilePath = "");

    // Delete whole trie
    void deleteTrie(TrieNode*& root);

    // Automatically delete the map and serialize it to the sourceFilePath (decided at the deserialization/construction)
	~Trie();

	/* -------------- CUSTOM FUNCTIONS --------------------- */

    // Return false if allocation failed, true if successfully inserted
	bool insertWord(const std::string& word, long long hashIndex = -1);

    // Return -1 if no word found, else return a hashIndex that is the index of a node in the balanced BST -> hashIndex is to find that node
	long long searchWord(const std::string& word);

    // Return false if no word found, otherwise remove and return true
	bool removeWord(const std::string& word);

    // Display all words in sorted order
	void displayTrie();
};

#endif // !TRIE_H
