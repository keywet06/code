#include <bits/stdc++.h>

#include "DAKLQW.h"

const int C1 = 10;
const int C2 = 15;
const int D1 = 1 << C1;
const int D2 = 1 << C2;

int r, f1, f2;

std::map<int, char> map;

std::set<int> p1[D1];
std::set<int> p2[D2];

char gettpos(int x) { return (map[x] ? map[x] : map[x] = getpos(x)) ^ '0'; }

int gettest(int x, int C) {
    int f = 0;
    for (int i = 0; i < C; ++i) f = f << 1 | gettpos(x + i + 1);
}

int realtest(int x, std::string &T, int &M, int &N) {
    if (x < 0 || x + M - 1 >= N) return 0;
    for (int i = 0; i < M; ++i) {
        if ((T[i] ^ '0') != gettpos(x + i + 1)) return 0;
    }
    return 1;
}

int xpptxdy(int N, std::string T) {
    map.clear();
    for (int i = 0; i < D1; ++i) p1[i].clear();
    for (int i = 0; i < D2; ++i) p2[i].clear();
    int M = T.length();
    r = 0;
    for (int i = M - C1 + 1; i < M; ++i) r = r << 1 | (T[i] ^ '0');
    r <<= 1;
    for (int i = M - C1; ~i; --i) p1[r = r >> 1 | ((T[i] ^ '0') << C1)];
    for (int i = 0; i < N; i += M - C2) {
        f1 = gettest(i, C1);
        if (p1[f1].empty()) continue;
        f2 = gettest(i, C2);
        for (int x : p2[f2]) {
            if (realtest(i - x, T, M, N)) return i - x + 1;
        }
    }
}