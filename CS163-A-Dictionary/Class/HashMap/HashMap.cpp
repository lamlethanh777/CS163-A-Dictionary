#include "HashMap.h"
#include <filesystem>

string llToStr(long long val) {
    if (val == 0) return "0";
    string ans = "";
    bool isNeg = (val < 0);
    val = abs(val);

    while (val != 0) {
        ans += (val % 10) + '0';
        val /= 10;
    }

    if (isNeg) ans += '-';
    reverse(ans.begin(), ans.end());

    return ans;
}

/*--------------------BST START AND ENDING FUNCTIONS-------------------*/
BinarySearchTree::BinarySearchTree(const string& hashMapFilePath, const long long& lb, const long long& rb) {
    root = new TreeNode((lb + rb) >> 1LL, 0);
    this->sourceFilePath = hashMapFilePath;
    this->leftBound = lb;
    this->rightBound = rb;

    deserialize();
}

BinarySearchTree::~BinarySearchTree() {
    //cout << "Destructor was called" << endl;
    serialize();
    clear(root);
}

void BinarySearchTree::buildOriginal() {
    std::string line;

    int lastPos = sourceFilePath.find_last_of("//");
    string originalFilePath = sourceFilePath.substr(0, lastPos + 1);
    originalFilePath += "Original.txt";
    //cout << originalFilePath << endl;

    std::ifstream fin;
    fin.open(originalFilePath, ifstream::in);
    if (!fin.is_open()) cout << "The file was errored, please try again!!" << endl;

    vector<Data>  fullData;
    while (getline(fin, line)) {
        Data data;
        string currString = "";
        for (int i = 0; i < (int)line.length(); ++i) {
            currString += line[i];

            //word
            if (line[i] == '`') {
                currString.pop_back();
                data.word = currString;
                currString.clear();
            }

            //definition
            else if (line[i] == '#') {
                currString.pop_back();
                data.definitions.push_back(currString);
                currString.clear();
            }
        }

        //last definitions
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

void BinarySearchTree::serializeNode(std::ofstream& fout, TreeNode* pRoot) {
    if (pRoot == nullptr) return;

    if (pRoot->data.num > 0) {
        string line = "";
        line += llToStr(pRoot->data.val) + ' ';
        line += pRoot->data.word + '`';
        for (const auto& it : pRoot->data.definitions) {
            line += it + '#';
        }

        fout << line << '\n';
    }

    serializeNode(fout, pRoot->pLeft);
    serializeNode(fout, pRoot->pRight);
}

void BinarySearchTree::serialize() {
    std::ofstream fout;
    fout.open(sourceFilePath, ofstream::out);

    //cout << sourceFilePath << endl;
    //if (!fout.is_open()) cout << "WTF WHY CAN NOT OPEN" << endl;

    serializeNode(fout, root);
    fout.close();
}

void BinarySearchTree::deserialize() {
    std::string line;

    std::ifstream fin;
    fin.open(sourceFilePath, ifstream::in);

    bool firstSpace = false;
    while (getline(fin, line)) {
        Data data;
        string currString = "";
        for (int i = 0; i < (int)line.length(); ++i) {
            currString += line[i];

            //hashValue
            if (line[i] == ' ' && !firstSpace) {
                firstSpace = true;
                currString.pop_back();
                data.val = stoll(currString);
                currString.clear();
            }

            //word
            else if (line[i] == '`') {
                currString.pop_back();
                data.word = currString;
                currString.clear();
            }

            //definition
            else if (line[i] == '#') {
                currString.pop_back();
                data.definitions.push_back(currString);
                currString.clear();
            }
        }

        //last definitions
        if (!currString.empty()) {
            data.definitions.push_back(currString);
        }

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

void BinarySearchTree::print(TreeNode* pRoot) {
    queue<TreeNode*> q;
    q.push(pRoot);
    while (q.size()) {
        TreeNode* u = q.front(); q.pop();
        if (u == nullptr) continue;
        if (u->data.num > 0)
            cout << u->data.val << "\n";
        q.push(u->pLeft);
        q.push(u->pRight);
    }
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
        cout << pRoot->data.val << " ";
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
    if (x > y) swap(x, y);
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

void BinarySearchTree::buildTree(vector<Data> & a) {
    for (auto& it : a) insert(root, it);
}

void BinarySearchTree::buildTree(vector <long long>& a) {
    for (auto& it : a) insert(root, Data(it, 1));
}

void BinarySearchTree::buildTree(vector <string>& a) {
    for (auto& it : a) {
        hashMod curHash = hashMod(it);
        insert(root, Data(curHash.getHash(), 1));
    }
}

TreeNode* BinarySearchTree::remove(TreeNode*& pRoot, const long long& val, long long lb, long long rb) {
    if (lb == -1 && rb == -1) lb = leftBound, rb = rightBound;
    long long mid = (lb + rb) >> 1LL;

    if (mid == val) {
        pRoot->data.clear();

        if (pRoot->pLeft == nullptr && pRoot->pRight == nullptr) {
            pRoot->data.clear();
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

pair<TreeNode*, bool> BinarySearchTree::remove(const long long& val) {
    TreeNode* curNode = searchVal(root, val);
    if (!curNode) return { root, false };

    return { remove(root, val), true };
}

/* -------------- CUSTOM FUNCTIONS --------------------- */

//Search word
TreeNode* BinarySearchTree::searchWord(const string& word) {
    if (word.empty()) return nullptr;
    hashMod curHash = hashMod(word);

    return searchVal(root, curHash.getHash());
}

//Get definitions
vector <string> BinarySearchTree::getDefinitions(const string& word) {
    hashMod curHash = hashMod(word);

    //Not found
    TreeNode* curNode = searchVal(root, curHash.getHash());
    if (!curNode) return vector <string>();

    return curNode->data.definitions;
}

//Insert word
TreeNode* BinarySearchTree::insertWord(const string& word) {
    if (word.empty()) return nullptr;
    hashMod curHash = hashMod(word);
    return insert(root, Data(curHash.getHash(), 1));
}

//Insert definition
TreeNode* BinarySearchTree::insertDefinition(const string& word, const string& definition) {
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
bool BinarySearchTree::removeWord(const string& word) {
    if (word.empty()) return false;
    hashMod curHash = hashMod(word);

    pair <TreeNode*, bool> res = remove(curHash.getHash());
    root = res.first;

    return res.second;
}