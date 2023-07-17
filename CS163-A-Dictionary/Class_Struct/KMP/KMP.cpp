#include "KMP.h"

KMP::KMP(const string& s) : s(s) {
    n = s.size();
    prefix.resize(n);

    calcPrefix();
}


void KMP::calcPrefix() {
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

bool KMP::isSubstring(const string& bigString) {
    int j = 0;
    for (int i = 0; i < bigString.size(); ++i) {
        while (j > 0 && bigString[i] != s[j]) j = prefix[j - 1];
        if (bigString[i] == s[j]) ++j;

        if (j == (int)s.length()) {
            return true;
        }
    }

    return false;
}