#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#include "tree.h"

const int C = 20;
const int N = 131072;

int Id[N], Num[N], Po[N], TPo[N];
int Con[C][N];

std::vector<std::pair<int, int>> solve(int n) {
    int k = 1;
    while (1) {
        int Tmp = 1;
        for (int i = 1; i <= k; ++i) {
            Tmp = Tmp * (k * 2 - i + 1) / i;
            if (Tmp >= n - 1) break;
        }
        if (Tmp >= n - 1) break;
        ++k;
    }
    int q = k * 2;
    std::vector<std::vector<int>> Que(q);
    std::vector<std::vector<std::vector<int>>> Sec(q);
    for (int i = 0; i < q; ++i) Que[i].resize(n - 1);
    for (int i = 0, ed = n - 1, Es = (1 << k) - 1; i < ed; ++i) {
        for (int j = 0; j < q; ++j) Que[j][i] = bool(Es & (1 << j));
        Es += Es & -Es, Es |= (1 << k - __builtin_popcount(Es)) - 1;
    }
    for (int i = 0; i < q; ++i) {
        Sec[i] = query(Que[i]);
        int Cnt = 0;
        for (auto v : Sec[i]) {
            for (auto x : v) Con[i][x] = Cnt;
            ++Cnt;
        }
    }
    std::vector<std::pair<int, int>> Ans;
    std::function<void(int, int, int, int)> Dfs = [&](int l, int r, int c, int e) -> void {
        if (r - l <= 1) return;
        if (r - l == 2) return void(Ans.emplace_back(Po[l], Po[l + 1]));
        if (e == k || c == q) return;
        if (q - c + e > k) Dfs(l, r, c + 1, e);
        int ICnt = 0;
        for (int i = l; i < r; ++i) {
            if (++Num[Con[c][Po[i]]] == 1) Id[ICnt++] = Con[c][Po[i]];
        }
        for (int i = 1; i < ICnt; ++i) Num[Id[i]] += Num[Id[i - 1]];
        memcpy(TPo + l, Po + l, sizeof(int) * (r - l));
        for (int i = l; i < r; ++i) Po[l + --Num[Con[c][TPo[i]]]] = TPo[i];
        for (int i = 0; i < ICnt; ++i) Num[Id[i]] = 0;
        while (l < r) {
            int t = l + 1;
            while (t < r && Con[c][Po[t - 1]] == Con[c][Po[t]]) ++t;
            Dfs(l, t, c + 1, e + 1), l = t;
        }
    };
    for (int i = 0; i < n; ++i) Po[i] = i;
    Dfs(0, n, 0, 0);
    for (auto &[u, v] : Ans) {
        if (u > v) std::swap(u, v);
    }
    std::sort(Ans.begin(), Ans.end());
    Ans.resize(std::unique(Ans.begin(), Ans.end()) - Ans.begin());
    return Ans;
}
