#include <bits/stdc++.h>

const int C = 20;
const int E = 1 << C;
const int N = 1 << C + 1;
const int R = E - 1;

struct trie : public std::bitset<N> {
    std::bitset<N> &th = *this;

    void insert(int x) {
        x |= E;
        while (x) th[x] = 1, x >>= 1;
    }

    void insertOr(int x) {
        insert(x);
        for (int i = 1; i < E; i <<= 1) {
            if (x & i && !th[E | x ^ i]) insertOr(x ^ i);
        }
    }

    int getXor(int x) {
        int ret = 0, u = 1, t;
        for (int i = 1 << C - 1; i; i >>= 1) {
            if (t = th[u << 1 | !(x & i)]) ret |= i;
            u = u << 1 | t ^ bool(x & i);
        }
        return ret;
    }

    int getOr(int x) { return getXor(x); }

    int getAnd(int x) { return getOr(R ^ x) ^ R ^ x; }
};

int q, o, x;

trie txor, tor;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> q;
    while (q--) {
        std::cin >> o >> x;
        if (o == 1) {
            txor.insert(x), tor.insertOr(x);
        } else if (o == 2) {
            std::cout << txor.getXor(x) << ' ' << tor.getAnd(x) << ' '
                      << tor.getOr(x) << '\n';
        } else {
            std::cout << txor.getXor(x) << '\n';
        }
    }
    return 0;
}