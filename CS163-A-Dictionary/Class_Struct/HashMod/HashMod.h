#ifndef HASH_MOD_H
#define HASH_MOD_H

#include<string>
#include<vector>

struct hashMod {
    int mod1 = 1e9 + 7, mod2 = 998244353, len = 0;
    std::vector <int> pw1, hash1, pw2, hash2;

    hashMod(std::string s, int baseHash = 331, int p1 = (int)1e9 + 7, int p2 = (int)998244353) : mod1(p1), mod2(p2) {
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

#endif // !HASH_MOD_H
