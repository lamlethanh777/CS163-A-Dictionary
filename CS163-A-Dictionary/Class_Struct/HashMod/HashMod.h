#ifndef HASH_MOD_H
#define HASH_MOD_H

#include<string>
#include<vector>

struct hashMod {
    int mod = 1e9 + 7, len = 0;
    std::vector <int> pw, hash;

    hashMod(std::string s, int baseHash = 331, int p = (int)1e9 + 7) : mod(p) {
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

#endif // !HASH_MOD_H
