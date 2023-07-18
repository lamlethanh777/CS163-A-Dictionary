//Copyright by cuom1999
#ifndef KMP_H
#define KMP_H

#include<string>
#include<vector>

using namespace std;

struct KMP {
    int n;
    string s;

    vector<int> prefix;

    KMP(const string& s);

    void calcPrefix();

    bool isSubstring(const string& bigString);
};

#endif
