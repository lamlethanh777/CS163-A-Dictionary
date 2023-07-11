#include "HashMap.h"

#include <random>
#include <chrono>
#include <iostream>

//std::string llToStr(long long val) {
//    if (val == 0) return "0";
//    std::string ans = "";
//    bool isNeg = (val < 0);
//    val = abs(val);
//
//    while (val != 0) {
//        ans += (val % 10) + '0';
//        val /= 10;
//    }
//
//    if (isNeg) ans += '-';
//    reverse(ans.begin(), ans.end());
//
//    return ans;
//}

/*--------------------BST START AND ENDING FUNCTIONS-------------------*/

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
    leftBound = 0; rightBound = 1e18;
    sourceFilePath = "";
}

// Automatically build map from the serialized file (HashMap.txt), sourceFilePath is set to HashMap.txt by default
BinarySearchTree::BinarySearchTree(const std::string& hashMapFilePath, const long long& lb, const long long& rb) {
    root = new TreeNode((lb + rb) >> 1LL, 0);
    this->sourceFilePath = hashMapFilePath;
    this->leftBound = lb;
    this->rightBound = rb;

    deserialize();
}

// Automatically delete the map and serialize it to the sourceFilePath (decided at the deserialization/construction)
BinarySearchTree::~BinarySearchTree() {
    //serialize();
    clear(root);
    std::cout << "Map destructor called!\n";
}

// Build Map from the original file (Original.txt), sourceFilePath is set to HashMap.txt by default
void BinarySearchTree::buildOriginal(const std::string inputedSourceFilePath) {
    std::string line;
    std::string originalFilePath;

    if (inputedSourceFilePath.compare("") == 0) {
        int lastPos = sourceFilePath.find_last_of("//");
        originalFilePath = sourceFilePath.substr(0, lastPos + 1) + "Original.txt";
    }
    else {
        originalFilePath = inputedSourceFilePath;
    }

    std::ifstream fin;
    readFile(fin, originalFilePath);

    std::vector<Data> fullData;
    while (getline(fin, line)) {
        Data data;
        std::string currString = "";

        //word
        int pos = line.find_last_of('`');
        currString = line.substr(0, pos);
        data.word = currString;
        currString.clear();

        //definitions
        for (unsigned int i = pos + 1; i < line.length(); ++i) {
            currString += line[i];
            if (line[i] == '#') {
                currString.pop_back();
                data.definitions.push_back(currString);
                currString.clear();
            }
        }

        //last definition
        if (!currString.empty()) {
            data.definitions.push_back(currString);
        }

        hashMod curHash(data.word);
        data.val = curHash.getHash();
        data.num = 1;

        fullData.push_back(data);
    }

    buildTree(fullData);
    fin.close();
}

// Helper
void BinarySearchTree::serializeNode(std::ofstream& fout, TreeNode* pRoot) {
    if (pRoot == nullptr) return;

    if (pRoot->data.num > 0) {
        std::string line = "";
        line += std::to_string(pRoot->data.val) + ' ';
        line += pRoot->data.word + '`';
        for (const auto& it : pRoot->data.definitions) {
            line += it + '#';
        }

        line.pop_back(); // Putting '#' at the end of a line causing the data to store unnecessary string -> see line 155->163
        fout << line << '\n';
    }

    serializeNode(fout, pRoot->pLeft);
    serializeNode(fout, pRoot->pRight);
}

// Manually serialize Map to (set sourceFilePath to): 1. serialized file (HashMap.txt) by default or 2. inputedSourceFilePath
void BinarySearchTree::serialize(const std::string inputedSourceFilePath) {
    if (inputedSourceFilePath.compare("") != 0) {
        sourceFilePath = inputedSourceFilePath;
    }

    std::ofstream fout;
    writeFile(fout, sourceFilePath);
    serializeNode(fout, root);
    fout.close();
}

// Manually deserialize (build) Map from (set sourceFilePath to): 1. serialized file (HashMap.txt) by default or 2. inputedSourceFilePath
void BinarySearchTree::deserialize(const std::string inputedSourceFilePath) {
    std::string line;

    if (inputedSourceFilePath.compare("") != 0) {
        sourceFilePath = inputedSourceFilePath;
    }

    std::ifstream fin;
    readFile(fin, sourceFilePath);

    while (getline(fin, line)) {
        Data data;
        std::string currString = "";
        
        //hashValue
        int firstSpace = line.find_first_of(' ');
        currString = line.substr(0, firstSpace);
        data.val = stoll(currString);
        currString.clear();

        //word
        int delimiter = line.find_last_of('`');
        currString = line.substr(firstSpace + 1, delimiter - firstSpace - 1);
        data.word = currString;
        currString.clear();

        //definitions
        for (unsigned int i = delimiter + 1; i < line.length(); ++i) {
            currString += line[i];
            if (line[i] == '#') {
                currString.pop_back();
                data.definitions.push_back(currString);
                currString.clear();
            }
        }

        //last definition
        if (!currString.empty()) {
            data.definitions.push_back(currString);
        }

        data.num = 1; // forgot this

        insert(data);
    }
    fin.close();
}

/*--------------------BST MAIN FUNCTIONS-------------------*/
void BinarySearchTree::clear(TreeNode*& pRoot) {
    if (!pRoot) return;
    clear(pRoot->pLeft);
    clear(pRoot->pRight);

    pRoot->data.clear();
    delete pRoot;
    pRoot = nullptr;
}

TreeNode* BinarySearchTree::searchVal(TreeNode* pRoot, const long long& x) {
    if (!pRoot) return nullptr;
    if (x == pRoot->data.val) return pRoot;
    if (x < pRoot->data.val) return searchVal(pRoot->pLeft, x);
    return searchVal(pRoot->pRight, x);
}

TreeNode* BinarySearchTree::searchParent(TreeNode* pRoot, const long long& x) {
    if (!pRoot) return nullptr;
    if ((pRoot->pLeft != nullptr && x == pRoot->pLeft->data.val) || (pRoot->pRight != nullptr && x == pRoot->pRight->data.val)) return pRoot;
    if (x < pRoot->data.val) return searchParent(pRoot->pLeft, x);
    return searchParent(pRoot->pRight, x);
}

void BinarySearchTree::printInRange(TreeNode* pRoot, const long long& x, const long long& y) {
    // cout << pRoot << " " << x << " " << y << endl;
    if (!pRoot) return;
    if (!(pRoot->data.val <= x))
        printInRange(pRoot->pLeft, x, y);
    if (x <= pRoot->data.val && pRoot->data.val <= y && pRoot->data.num > 0)
        std::cout << pRoot->data.val << " ";
    if (!(pRoot->data.val >= y)) {
        printInRange(pRoot->pRight, x, y);
    }
}

TreeNode* BinarySearchTree::getCCA(TreeNode* pRoot, const long long& x, const long long& y) {
    if (x <= pRoot->data.val && pRoot->data.val <= y) return pRoot;
    if (x > pRoot->data.val) return getCCA(pRoot->pRight, x, y);
    return getCCA(pRoot->pLeft, x, y);
}

TreeNode* BinarySearchTree::closestCommonAncestor(TreeNode* pRoot, long long x, long long y) {
    //Assume x < y
    if (x > y) std::swap(x, y);
    if (!searchVal(pRoot, x) || !searchVal(pRoot, y)) return nullptr;
    return getCCA(pRoot, x, y);
}

TreeNode* BinarySearchTree::insert(TreeNode*& pRoot, const Data& x, long long lb, long long rb) {
    if (lb == -1 && rb == -1) lb = leftBound, rb = rightBound;
    long long mid = (lb + rb) >> 1LL;
    if (pRoot == nullptr) pRoot = new TreeNode(mid, 0);

    if (mid == x.val) {
        pRoot->data.num += x.num;
        pRoot->data.word = x.word;
        for (const auto& it : x.definitions) pRoot->data.definitions.push_back(it);
        return pRoot;
    }

    if (x.val < mid) return insert(pRoot->pLeft, x, lb, mid - 1);
    return insert(pRoot->pRight, x, mid + 1, rb);
}

TreeNode* BinarySearchTree::insert(const Data& x) {
    return insert(root, x);
}

TreeNode* BinarySearchTree::insert(const long long& x) {
    return insert(root, Data(x, 1));
}

void BinarySearchTree::buildTree(std::vector<Data> & a) {
    for (auto& it : a) insert(root, it);
}

void BinarySearchTree::buildTree(std::vector <long long>& a) {
    for (auto& it : a) insert(root, Data(it, 1));
}

void BinarySearchTree::buildTree(std::vector <std::string>& a) {
    for (auto& it : a) {
        hashMod curHash = hashMod(it);
        insert(root, Data(curHash.getHash(), 1));
    }
}

TreeNode* BinarySearchTree::remove(TreeNode*& pRoot, const long long& val, long long lb, long long rb) {
    if (lb == -1 && rb == -1) lb = leftBound, rb = rightBound;
    long long mid = (lb + rb) >> 1LL;

    if (mid == val) {
        pRoot->data.definitions.clear();
        pRoot->data.word = "";
        pRoot->data.val = 0;
        pRoot->data.num = 0;

        if (pRoot->pLeft == nullptr && pRoot->pRight == nullptr) {
            delete pRoot;
            pRoot = nullptr;
        }

        return pRoot;
    }

    if (val < mid) pRoot->pLeft = remove(pRoot->pLeft, val, lb, mid - 1);
    else pRoot->pRight = remove(pRoot->pRight, val, mid + 1, rb);

    if (pRoot->pLeft == nullptr && pRoot->pRight == nullptr) {
        delete pRoot;
        pRoot = nullptr;
    }

    return pRoot;
}

std::pair<TreeNode*, bool> BinarySearchTree::remove(const long long& val) {
    TreeNode* curNode = searchVal(root, val);
    if (!curNode) return { root, false };

    return { remove(root, val), true };
}

/* -------------- CUSTOM FUNCTIONS --------------------- */

//Search word directyly (not suggested, as the trie already stores all the hashIndex)
TreeNode* BinarySearchTree::searchWord(const std::string& word) {
    if (word.empty()) return nullptr;
    hashMod curHash = hashMod(word);

    return searchVal(root, curHash.getHash());
}

//Search word by index (traversing through the trie and collecting hashIndex to search)
TreeNode* BinarySearchTree::searchWord(const long long& hashIndex) {
    return searchVal(root, hashIndex);
}

//Get definitions
std::vector <std::string> BinarySearchTree::getDefinitions(const std::string& word) {
    hashMod curHash = hashMod(word);

    //Not found
    TreeNode* curNode = searchVal(root, curHash.getHash());
    if (!curNode) return std::vector <std::string>();

    return curNode->data.definitions;
}

//Insert word
TreeNode* BinarySearchTree::insertWord(const std::string& word) {
    if (word.empty()) return nullptr;
    hashMod curHash = hashMod(word);
    return insert(root, Data(curHash.getHash(), 1, word));
}

//Insert definition
TreeNode* BinarySearchTree::insertDefinition(const std::string& word, const std::string& definition) {
    if (word.empty()) return nullptr;
    if (definition.empty()) return nullptr;

    hashMod curHash = hashMod(word);

    //Auto create TreeNode if word is not found
    TreeNode* curNode = searchVal(root, curHash.getHash());
    if (!curNode) curNode = insert(root, Data(curHash.getHash(), 1));

    curNode->data.definitions.push_back(definition);
    return curNode;
}

//Remove word
bool BinarySearchTree::removeWord(const std::string& word) {
    if (word.empty()) return false;
    hashMod curHash = hashMod(word);

    std::pair <TreeNode*, bool> res = remove(curHash.getHash());
    root = res.first;

    return res.second;
}

/* -------------- GAME FUNCTIONS --------------------- */
// Return the node of a random word
TreeNode* BinarySearchTree::randomNode() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    TreeNode* cur = root;
    
    while (cur != nullptr) {
        //CurrentNode is leaf
        if (cur->pLeft == nullptr && cur->pRight == nullptr) return cur;

        //Choose or not
        if (cur->data.num > 0) {
            bool isChosen = rng() % 2;
            if (isChosen) return cur;
        }

        //Go next
        bool goLeft = rng() % 2;
        if (goLeft) {
            if (cur->pLeft != nullptr) cur = cur->pLeft;
            else cur = cur->pRight;
        }

        else {
            if (cur->pRight != nullptr) cur = cur->pRight;
            else cur = cur->pLeft;
        }
    }
}

// Return a random quiz (see struct Quiz and read function definition) of 1 word and 4 definitions
Quiz BinarySearchTree::chooseRightDefinition() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    Data clonedData = randomNode()->data;
    remove(clonedData.val);

    Quiz currQuiz;
    currQuiz.question = clonedData.word;
    currQuiz.choices.push_back(*clonedData.definitions.begin());

    for (unsigned int i = 0; i < 3; ++i) {
        currQuiz.choices.push_back(*randomNode()->data.definitions.begin());
    }

    shuffle(currQuiz.choices.begin(), currQuiz.choices.end(), rng);
    for (unsigned int i = 0; i < 4; ++i) {
        if (currQuiz.choices[i] == *clonedData.definitions.begin()) {
            currQuiz.answer = i;
            break;
        }
    }

    insert(clonedData);
    return currQuiz;
}

// Return a random quiz (see struct Quiz and read function definition) or 1 definition and 4 words
Quiz BinarySearchTree::chooseRightWord() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    Data clonedData = randomNode()->data;
    remove(clonedData.val);

    Quiz currQuiz;
    currQuiz.question = *clonedData.definitions.begin();
    currQuiz.choices.push_back(clonedData.word);

    for (unsigned int i = 0; i < 3; ++i) {
        currQuiz.choices.push_back(randomNode()->data.word);
    }

    shuffle(currQuiz.choices.begin(), currQuiz.choices.end(), rng);
    for (unsigned int i = 0; i < 4; ++i) {
        if (currQuiz.choices[i] == clonedData.word) {
            currQuiz.answer = i;
            break;
        }
    }

    insert(clonedData);
    return currQuiz;
}
