//Copyright by cuom1999
#ifndef KMP_H
#define KMP_H

#include<string>
#include<vector>
#include<algorithm>

using namespace std;

// watchout 'A' and 'a'
struct KMP {
    // lsp[i]: longest proper suffix of s[0..i]
    // nextState[i][c]: next state if go from i through char c
    // state i: longest proper prefix = i
    
    int MAXC = 26;
    int n;
    string s;
 
    vector<int> compressedValue;
    vector<int> prefix;
    vector<vector<int>> nextState;

    void compress();
    void calcPrefix(); 
    void calcNextState();

    KMP(string s) : s(s) {
        n = s.size();
        prefix.resize(n);

        compress();
        calcPrefix();
        calcNextState();
    }

    void compress() {
        for (auto it : s) compressedValue.push_back(it);
        sort(compressedValue.begin(), compressedValue.end());
        
        compressedValue.erase(unique(compressedValue.begin(), compressedValue.end()), compressedValue.end());
        MAXC = (int)compressedValue.size();

        nextState.resize(n, vector<int>(MAXC));
    }

    void calcPrefix() {
        for (int i = 1; i < n; i++) {
            int k = prefix[i - 1];
            while (k && s[i] != s[k]) {
                k = prefix[k - 1];
            }

            if (s[i] == s[k]) {
                k++;
            }
            prefix[i] = k;
        }
    }

    void calcNextState() {
        for (int i = 0; i <= n; i++) {
            int currentVal = lower_bound(compressedValue.begin(), compressedValue.end(), (int)s[i]) - compressedValue.begin();
            for (int j = 0; j < MAXC; j++) {
                if (i == n || (i && j != currentVal)) {
                    nextState[i][j] = nextState[prefix[i - 1]][j];
                }
                else {
                    nextState[i][j] = i + (j == currentVal);
                }
            }
        }
    }

    bool isSubstring(string pattern) {
        int state = 0;
        for (auto it : pattern) {
            int currentVal = lower_bound(compressedValue.begin(), compressedValue.end(), (int)it) - compressedValue.begin();
            if (currentVal == (int)compressedValue.size() || compressedValue[currentVal] != (int)it) return false;

            state = nextState[state][currentVal];
        }
        
        return state == (int)pattern.size();    
    }

};

#endif