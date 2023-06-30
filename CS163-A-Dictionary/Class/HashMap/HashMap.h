#pragma once
#include <string>
#include <vector>
using namespace std;

struct hashMod {
    int mod1 = 1e9 + 7, mod2 = 998244353, len = 0;
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
    vector <string> definitions;

    Data(long long val = 0, int num = 0) {
        this->val = val;
        this->num = num;
    }

    void clear() {
        this->num = 0;
        this->definitions.clear();
    }
};

template <typename T> struct TreeNode {
    T data;
    TreeNode<T>* pLeft, * pRight;

    TreeNode(T x = T()) {
        data = x;
        pLeft = nullptr;
        pRight = nullptr;
    }

    TreeNode(long long x, int num = 0) {
        data = T(x, num);
        pLeft = nullptr;
        pRight = nullptr;
    }

    ~TreeNode() {
        delete pLeft;
        delete pRight;
    }
};

template <typename T> class BinarySearchTree {
public:
    TreeNode <T>* root;
    long long leftBound = 0, rightBound = 1e18;

    BinarySearchTree(long long lb = 0, long long rb = 1e18) {
        root = new TreeNode<T>((lb + rb) >> 1LL, 0);
        this->leftBound = lb;
        this->rightBound = rb;
    }

    void clear(TreeNode<T>*& pRoot) {
        if (!pRoot) return;
        clear(pRoot->pLeft);
        clear(pRoot->pRight);

        pRoot->data.clear();
        delete pRoot;
        pRoot = nullptr;
    }

    ~BinarySearchTree() {
        clear(root);
    }

    /*--------------------BST MAIN FUNCTIONS-------------------*/

    void print(TreeNode<T>* pRoot);

    void printInRange(TreeNode<T>* pRoot, const long long& x, const long long& y);

    TreeNode<T>* searchVal(TreeNode<T>* pRoot, const long long& x);

    TreeNode<T>* searchParent(TreeNode<T>* pRoot, const long long& x);

    TreeNode<T>* getCCA(TreeNode<T>* pRoot, const long long& x, const long long& y);

    TreeNode<T>* closestCommonAncestor(TreeNode<T>* pRoot, long long x, long long y);

    TreeNode<T>* insert(TreeNode<T>*& pRoot, const Data& x, long long lb = -1, long long rb = -1);

    TreeNode<T>* insert(const Data& x);

    TreeNode<T>* insert(const long long& x);

    void buildTree(vector <T>& a);

    void buildTree(vector <long long>& a);

    void buildTree(vector <string>& a);

    TreeNode<T>* remove(TreeNode<T>*& pRoot, const long long& val, long long lb = -1, long long rb = -1);

    pair<TreeNode<T>*, bool> remove(const long long& val);

    /* -------------- CUSTOM FUNCTIONS --------------------- */

    //Search word
    TreeNode<T>* searchWord(const string& word);

    //Get definitions
    vector <string> getDefinitions(const string& word);

    //Insert word
    TreeNode<T>* insertWord(const string& word);

    //Insert definition
    TreeNode<T>* insertDefinition(const string& word, const string& definition);

    //Remove word
    bool removeWord(const string& word);
};