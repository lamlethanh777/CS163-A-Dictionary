#ifndef HASHMAP_H
#define HASHMAP_H

#include "../HashMod/HashMod.h"
#include "../../Functions/Utilities/OpenFile/OpenFile.h"

std::string llToStr(long long val);

struct Quiz {
    std::string question;
    std::vector<std::string>choices;
    int answer;

    Quiz() {
        question = "";
        answer = 0;
    }
};

struct Data {
    long long val;
    int num;
    std::string word;
    std::vector <std::string> definitions;

    Data(long long val = 0, int num = 0, const std::string word = "") {
        this->val = val;
        this->num = num;
        this->word = word;
    }

    void clear() {
        this->num = 0;
        this->definitions.clear();
    }
};

struct TreeNode {
    Data data;
    TreeNode* pLeft, *pRight;

    TreeNode(Data x = Data()) {
        data = x;
        pLeft = nullptr;
        pRight = nullptr;
    }

    TreeNode(long long x, int num = 0) {
        data = Data(x, num);
        pLeft = nullptr;
        pRight = nullptr;
    }

    ~TreeNode() {
        delete pLeft;
        delete pRight;
    }
};

class BinarySearchTree {
public:
    /*--------------------BST START AND ENDING FUNCTIONS-------------------*/
    TreeNode* root = nullptr;
    long long leftBound = 0, rightBound = 1e18;
    std::string sourceFilePath;

    // Automatically build map from the serialized file (HashMap.txt), sourceFilePath is set to HashMap.txt by default
    BinarySearchTree(const std::string& hashMapFilePath, const long long& lb = 0, const long long& rb = (long long)1e18);
    
    // Automatically delete the map and serialize it to the sourceFilePath (decided at the deserialization/construction)
    ~BinarySearchTree();

    // Build Map from the original file (Original.txt), sourceFilePath is set to HashMap.txt by default
    void buildOriginal();

    // Helper
    void serializeNode(std::ofstream& fout, TreeNode* pRoot);

    // Manually serialize Map to (set sourceFilePath to): 1. serialized file (HashMap.txt) by default or 2. inputedSourceFilePath
    void serialize(const std::string inputedSourceFilePath = "");

    // Manually deserialize (build) Map from (set sourceFilePath to): 1. serialized file (HashMap.txt) by default or 2. inputedSourceFilePath
    void deserialize(const std::string inputedSourceFilePath = "");

    /*--------------------BST MAIN FUNCTIONS-------------------*/

    void clear(TreeNode*& pRoot);

    void printInRange(TreeNode* pRoot, const long long& x, const long long& y);

    TreeNode* searchVal(TreeNode* pRoot, const long long& x);

    TreeNode* searchParent(TreeNode* pRoot, const long long& x);

    TreeNode* getCCA(TreeNode* pRoot, const long long& x, const long long& y);

    TreeNode* closestCommonAncestor(TreeNode* pRoot, long long x, long long y);

    TreeNode* insert(TreeNode*& pRoot, const Data& x, long long lb = -1, long long rb = -1);

    TreeNode* insert(const Data& x);

    TreeNode* insert(const long long& x);

    void buildTree(std::vector<Data> & a);

    void buildTree(std::vector <long long>& a);

    void buildTree(std::vector <std::string>& a);

    TreeNode* remove(TreeNode*& pRoot, const long long& val, long long lb = -1, long long rb = -1);

    std::pair<TreeNode*, bool> remove(const long long& val);

    /* -------------- CUSTOM FUNCTIONS --------------------- */

    //Search word (not suggested, as the trie already stores all the hashIndex)
    TreeNode* searchWord(const std::string& word);

    //Search word by index (traversing through the trie and collecting hashIndex to search)
    TreeNode* searchWord(const long long& hashIndex);

    //Get definitions
    std::vector <std::string> getDefinitions(const std::string& word);

    //Insert word (word only)
    TreeNode* insertWord(const std::string& word);

    //Insert definition (insert/edit both word and definitions)
    TreeNode* insertDefinition(const std::string& word, const std::string& definition);

    //Remove word entirely
    bool removeWord(const std::string& word);

    /* -------------- GAME FUNCTIONS --------------------- */
    // Return the node of a random word
    TreeNode* randomNode();

    // Return a random quiz (see struct Quiz and read function definition) of 1 word and 4 definitions
    Quiz chooseRightDefinition();

    // Return a random quiz (see struct Quiz and read function definition) or 1 definition and 4 words
    Quiz chooseRightWord();
};

#endif
