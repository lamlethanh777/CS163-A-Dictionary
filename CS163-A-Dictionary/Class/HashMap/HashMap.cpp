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
};

template <typename T> struct BinarySearchTree {
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

    /*--------------------BST MAIN FUNCTIONS-------------------*/

    void print(TreeNode<T>* pRoot) {
        queue<TreeNode<T>*> q;
        q.push(pRoot);
        while (q.size()) {
            TreeNode<T>* u = q.front(); q.pop();
            if (u == nullptr) continue;
            if (u->data.num > 0)
                cout << u->data.val << "\n";
            q.push(u->pLeft);
            q.push(u->pRight);
        }
    }

    TreeNode<T>* searchVal(TreeNode<T>* pRoot, int x) {
        if (!pRoot) return nullptr;
        if (x == pRoot->data.val) return pRoot;
        if (x < pRoot->data.val) return searchVal(pRoot->pLeft, x);
        return searchVal(pRoot->pRight, x);
    }

    TreeNode<T>* searchParent(TreeNode<T>* pRoot, int x) {
        if (!pRoot) return nullptr;
        if (x == pRoot->pLeft->data.val || x == pRoot->pRight->data.val) return pRoot;
        if (x < pRoot->data.val) return searchParent(pRoot->pLeft, x);
        return searchParent(pRoot->pRight, x);
    }

    void printInRange(TreeNode<T>* pRoot, int x, int y) {
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

    TreeNode<T>* getCCA(TreeNode<T>* pRoot, int x, int y) {
        if (x <= pRoot->data.val && pRoot->data.val <= y) return pRoot;
        if (x > pRoot->data.val) return getCCA(pRoot->pRight, x, y);
        return getCCA(pRoot->pLeft, x, y);
    }

    TreeNode<T>* closestCommonAncestor(TreeNode<T>* pRoot, int x, int y) {
        //Assume x < y
        if (x > y) swap(x, y);
        if (!searchVal(pRoot, x) || !searchVal(pRoot, y)) return nullptr;
        return getCCA(pRoot, x, y);
    }

    TreeNode<T>* insert(TreeNode<T>*& pRoot, Data x, int lb = -1, int rb = -1) {
        if (lb == -1 && rb == -1) lb = leftBound, rb = rightBound;
        int mid = (lb + rb) >> 1;
        if (pRoot == nullptr) pRoot = new TreeNode<T>(mid, 0);

        if (mid == x.val) {
            pRoot->data.num += x.num;
            return pRoot;
        }

        if (x.val < mid) return insert(pRoot->pLeft, x, lb, mid - 1);
        return insert(pRoot->pRight, x, mid + 1, rb);
    }

    TreeNode <T>* insert(Data x) {
        return insert(root, x);
    }

    TreeNode<T>* insert(int x) {
        return insert(root, Data(x, 1));
    }

    void buildTree(vector <T>& a) {
        for (auto& it : a) insert(root, it);
    }

    void buildTree(vector <int>& a) {
        for (auto& it : a) insert(root, Data(it, 1));
    }

    void buildTree(vector <string>& a) {
        for (auto& it : a) {
            hashMod curHash = hashMod(it);
            insert(root, Data(curHash.getHash(), 1));
        }
    }

    TreeNode<T>* remove(TreeNode<T>*& pRoot, int val, int lb = -1, int rb = -1) {
        if (lb == -1 && rb == -1) lb = leftBound, rb = rightBound;
        int mid = (lb + rb) >> 1;

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

    TreeNode<T>* remove(int val) {
        TreeNode<T>* curNode = searchVal(root, val);
        if (!curNode) return nullptr;

        return remove(root, val);
    }

    /* -------------- CUSTOM FUNCTIONS --------------------- */

    //Search word
    TreeNode<T>* searchWord(string word) {
        if (word.empty()) return nullptr;
        hashMod curHash = hashMod(word);

        return searchVal(root, curHash.getHash());
    }

    //Get definitions
    vector <string> getDefinitions(string word) {
        hashMod curHash = hashMod(word);

        //Not found
        TreeNode<T>* curNode = searchVal(root, curHash.getHash());
        if (!curNode) return vector <string>();

        return curNode->data.definitions;
    }

    //Insert word
    TreeNode<T>* insert(string word) {
        if (word.empty()) return nullptr;
        hashMod curHash = hashMod(word);
        return insert(root, Data(curHash.getHash(), 1));
    }

    //Insert definition
    TreeNode<T>* insert(string word, string definition) {
        if (word.empty()) return nullptr;
        hashMod curHash = hashMod(word);

        //Auto create TreeNode if word is not found
        TreeNode<T>* curNode = searchVal(root, curHash.getHash());
        if (!curNode) curNode = insert(root, Data(curHash.getHash(), 1));

        curNode->data.definitions.push_back(definition);
        return curNode;
    }

    //Remove word
    TreeNode<T>* remove(string word) {
        if (word.empty()) return nullptr;
        hashMod curHash = hashMod(word);
        return root = remove(curHash.getHash());
    }
};
