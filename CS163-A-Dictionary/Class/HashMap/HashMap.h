#pragma once
#include <string>
#include <vector>
using namespace std;

struct hashMod {
    int mod = 1e9 + 7, len = 0;
    vector <int> pw, hash;

    hashMod(string s, int baseHash = 331, int p = (int)1e9 + 7) : mod(p) {
        int n = (int)s.size();
        len = n;
        pw.resize(n + 5); hash.resize(n + 5);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) pw[i] = (1LL * pw[i - 1] * baseHash) % mod;

        hash[0] = s[0];
        for (int i = 1; i < n; ++i) {
            hash[i] = (1LL * hash[i - 1] * baseHash + s[i]) % mod;
        }
    }

    int getHash() {
        return hash[len - 1];
    }

    int getHash(int l, int r) {
        if (!l) return hash[r];
        return (1LL * hash[r] - 1LL * hash[l - 1] * pw[r - l + 1] + 1LL * mod * mod) % mod;
    }
};

struct Data {
    int val, num;
    vector <string> definitions;

    Data(int val = 0, int num = 0) {
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

    TreeNode(int x, int num = 0) {
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
    int leftBound = 0, rightBound = 1e9 + 10;

    BinarySearchTree(int lb = 0, int rb = 1e9 + 10) {
        root = new TreeNode<T>((lb + rb) >> 1, 0);
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

    void printInRange(TreeNode<T>* pRoot, int x, int y);

    TreeNode<T>* searchVal(TreeNode<T>* pRoot, int x);

    TreeNode<T>* searchParent(TreeNode<T>* pRoot, int x);

    TreeNode<T>* getCCA(TreeNode<T>* pRoot, int x, int y);

    TreeNode<T>* closestCommonAncestor(TreeNode<T>* pRoot, int x, int y);

    TreeNode<T>* insert(TreeNode<T>*& pRoot, Data x, int lb = -1, int rb = -1);

    TreeNode<T>* insert(Data x);

    TreeNode<T>* insert(int x);

    void buildTree(vector <T>& a);

    void buildTree(vector <int>& a);

    void buildTree(vector <string>& a);

    TreeNode<T>* remove(TreeNode<T>*& pRoot, int val, int lb = -1, int rb = -1);

    TreeNode<T>* remove(int val);

    /* -------------- CUSTOM FUNCTIONS --------------------- */

    //Search word
    TreeNode<T>* searchWord(string word);

    //Get definitions
    vector <string> getDefinitions(string word);

    //Insert word
    TreeNode<T>* insert(string word);

    //Insert definition
    TreeNode<T>* insert(string word, string definition);

    //Remove word
    TreeNode<T>* remove(string word);
};