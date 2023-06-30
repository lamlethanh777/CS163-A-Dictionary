#include "HashMap.h"

/*--------------------BST MAIN FUNCTIONS-------------------*/
template <typename T>
void BinarySearchTree<T>::print(TreeNode<T>* pRoot) {
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

template <typename T>
TreeNode<T>* BinarySearchTree<T>::searchVal(TreeNode<T>* pRoot, const long long& x) {
    if (!pRoot) return nullptr;
    if (x == pRoot->data.val) return pRoot;
    if (x < pRoot->data.val) return searchVal(pRoot->pLeft, x);
    return searchVal(pRoot->pRight, x);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::searchParent(TreeNode<T>* pRoot, const long long& x) {
    if (!pRoot) return nullptr;
    if ((pRoot->pLeft != nullptr && x == pRoot->pLeft->data.val) || (pRoot->pRight != nullptr && x == pRoot->pRight->data.val)) return pRoot;
    if (x < pRoot->data.val) return searchParent(pRoot->pLeft, x);
    return searchParent(pRoot->pRight, x);
}

template <typename T>
void BinarySearchTree<T>::printInRange(TreeNode<T>* pRoot, const long long& x, const long long& y) {
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

template <typename T>
TreeNode<T>* BinarySearchTree<T>::getCCA(TreeNode<T>* pRoot, const long long& x, const long long& y) {
    if (x <= pRoot->data.val && pRoot->data.val <= y) return pRoot;
    if (x > pRoot->data.val) return getCCA(pRoot->pRight, x, y);
    return getCCA(pRoot->pLeft, x, y);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::closestCommonAncestor(TreeNode<T>* pRoot, long long x, long long y) {
    //Assume x < y
    if (x > y) swap(x, y);
    if (!searchVal(pRoot, x) || !searchVal(pRoot, y)) return nullptr;
    return getCCA(pRoot, x, y);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>*& pRoot, const Data& x, long long lb, long long rb) {
    if (lb == -1 && rb == -1) lb = leftBound, rb = rightBound;
    long long mid = (lb + rb) >> 1LL;
    if (pRoot == nullptr) pRoot = new TreeNode<T>(mid, 0);

    if (mid == x.val) {
        pRoot->data.num += x.num;
        return pRoot;
    }

    if (x.val < mid) return insert(pRoot->pLeft, x, lb, mid - 1);
    return insert(pRoot->pRight, x, mid + 1, rb);
}

template <typename T>
TreeNode <T>* BinarySearchTree<T>::insert(const Data& x) {
    return insert(root, x);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert(const long long& x) {
    return insert(root, Data(x, 1));
}

template <typename T>
void BinarySearchTree<T>::buildTree(vector <T>& a) {
    for (auto& it : a) insert(root, it);
}

template <typename T>
void BinarySearchTree<T>::buildTree(vector <long long>& a) {
    for (auto& it : a) insert(root, Data(it, 1));
}

template <typename T>
void BinarySearchTree<T>::buildTree(vector <string>& a) {
    for (auto& it : a) {
        hashMod curHash = hashMod(it);
        insert(root, Data(curHash.getHash(), 1));
    }
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::remove(TreeNode<T>*& pRoot, const long long& val, long long lb, long long rb) {
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

template <typename T>
pair<TreeNode<T>*, bool> BinarySearchTree<T>::remove(const long long& val) {
    TreeNode<T>* curNode = searchVal(root, val);
    if (!curNode) return { root, false };

    return { remove(root, val), true };
}

/* -------------- CUSTOM FUNCTIONS --------------------- */

//Search word
template <typename T>
TreeNode<T>* BinarySearchTree<T>::searchWord(const string& word) {
    if (word.empty()) return nullptr;
    hashMod curHash = hashMod(word);

    return searchVal(root, curHash.getHash());
}

//Get definitions
template <typename T>
vector <string> BinarySearchTree<T>::getDefinitions(const string& word) {
    hashMod curHash = hashMod(word);

    //Not found
    TreeNode<T>* curNode = searchVal(root, curHash.getHash());
    if (!curNode) return vector <string>();

    return curNode->data.definitions;
}

//Insert word
template <typename T>
TreeNode<T>* BinarySearchTree<T>::insertWord(const string& word) {
    if (word.empty()) return nullptr;
    hashMod curHash = hashMod(word);
    return insert(root, Data(curHash.getHash(), 1));
}

//Insert definition
template <typename T>
TreeNode<T>* BinarySearchTree<T>::insertDefinition(const string& word, const string& definition) {
    if (word.empty()) return nullptr;
    if (definition.empty()) return nullptr;

    hashMod curHash = hashMod(word);

    //Auto create TreeNode if word is not found
    TreeNode<T>* curNode = searchVal(root, curHash.getHash());
    if (!curNode) curNode = insert(root, Data(curHash.getHash(), 1));

    curNode->data.definitions.push_back(definition);
    return curNode;
}

//Remove word
template <typename T>
bool BinarySearchTree<T>::removeWord(const string& word) {
    if (word.empty()) return false;
    hashMod curHash = hashMod(word);

    pair <TreeNode<T>*, bool> res = remove(curHash.getHash());
    root = res.first;

    return res.second;
}