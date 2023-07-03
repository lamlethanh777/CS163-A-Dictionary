#ifndef HASHMAP_H
#define HASHMAP_H

#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string llToStr(long long val);

struct Quiz {
    string question;
    vector<string>choices;
    int answer;

    Quiz() {
        question = "";
        answer = 0;
    }
};

struct hashMod {
    int mod1 = (int)1e9 + 7, mod2 = 998244353, len = 0;
    vector <int> pw1, hash1, pw2, hash2;

    hashMod(string s, int baseHash = 331, int p1 = (int)1e9 + 7, int p2 = (int)998244353) : mod1(p1), mod2(p2) {
        int n = (int)s.size();
        len = n;
        pw1.resize(n + 2); hash1.resize(n + 2);
        pw2.resize(n + 2); hash2.resize(n + 2);

        pw1[0] = pw2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pw1[i] = (1LL * pw1[i - 1] * baseHash) % mod1;
            pw2[i] = (1LL * pw2[i - 1] * baseHash) % mod2;
        }

        hash1[0] = hash2[0] = s[0];
        for (int i = 1; i < n; ++i) {
            hash1[i] = (1LL * hash1[i - 1] * baseHash + s[i]) % mod1;
            hash2[i] = (1LL * hash2[i - 1] * baseHash + s[i]) % mod2;
        }
    }

    long long doubleHash(const int& hashMod1, const int& hashMod2) {
        return 1LL * hashMod1 * mod2 + hashMod2;
    }

    long long getHash() {
        return doubleHash(hash1[len - 1], hash2[len - 1]);
    }

    long long getHash(int l, int r) {
        if (!l) return doubleHash(hash1[r], hash2[r]);
        int hashMod1 = (1LL * hash1[r] - 1LL * hash1[l - 1] * pw1[r - l + 1] + 1LL * mod1 * mod1) % mod1;
        int hashMod2 = (1LL * hash2[r] - 1LL * hash2[l - 1] * pw2[r - l + 1] + 1LL * mod2 * mod2) % mod2;

        return doubleHash(hashMod1, hashMod2);
    }
};

struct Data {
    long long val;
    int num;
    string word;
    vector <string> definitions;

    Data(long long val = 0, int num = 0) {
        this->val = val;
        this->num = num;
        this->word = "";
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
    string sourceFilePath;

    BinarySearchTree(const string& hashMapFilePath, const long long& lb = 0, const long long& rb = (long long)1e18);
      
    ~BinarySearchTree();

    void buildOriginal();

    void serializeNode(std::ofstream& fout, TreeNode* pRoot);

    void serialize();

    void deserialize();

    /*--------------------BST MAIN FUNCTIONS-------------------*/

    void clear(TreeNode*& pRoot);

    void print(TreeNode* pRoot);

    void printInRange(TreeNode* pRoot, const long long& x, const long long& y);

    TreeNode* searchVal(TreeNode* pRoot, const long long& x);

    TreeNode* searchParent(TreeNode* pRoot, const long long& x);

    TreeNode* getCCA(TreeNode* pRoot, const long long& x, const long long& y);

    TreeNode* closestCommonAncestor(TreeNode* pRoot, long long x, long long y);

    TreeNode* insert(TreeNode*& pRoot, const Data& x, long long lb = -1, long long rb = -1);

    TreeNode* insert(const Data& x);

    TreeNode* insert(const long long& x);

    void buildTree(vector<Data> & a);

    void buildTree(vector <long long>& a);

    void buildTree(vector <string>& a);

    TreeNode* remove(TreeNode*& pRoot, const long long& val, long long lb = -1, long long rb = -1);

    pair<TreeNode*, bool> remove(const long long& val);

    /* -------------- CUSTOM FUNCTIONS --------------------- */

    //Search word
    TreeNode* searchWord(const string& word);

    //Get definitions
    vector <string> getDefinitions(const string& word);

    //Insert word
    TreeNode* insertWord(const string& word);

    //Insert definition
    TreeNode* insertDefinition(const string& word, const string& definition);

    //Remove word
    bool removeWord(const string& word);

    /* -------------- GAME FUNCTIONS --------------------- */
    TreeNode* randomNode();

    Quiz chooseRightDefinition();

    Quiz chooseRightWord();
};

#endif