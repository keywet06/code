#include <bits/stdc++.h>

using int64 = long long;

const int N = 10;
const int M = 500000;

int T, cnt, ans, l, r, u;
int vis[N];

int64 a[N];
int64 h[N][N];
int64 d[M][N];

std::unordered_map<int64, int> map;

void dfs(int c) {
    if (c == N) {
        for (int i = 1; i <= 9; ++i) h[cnt][i] = a[i];
        return void(++cnt);
    }
    for (int i = 1; i <= 9; ++i) {
        if (vis[i]) continue;
        if (c == 3 && a[1] + a[2] + i != 15) continue;
        if (c == 6 && a[4] + a[5] + i != 15) continue;
        if (c == 7 && a[1] + a[4] + i != 15) continue;
        if (c == 7 && a[3] + a[5] + i != 15) continue;
        if (c == 8 && a[2] + a[5] + i != 15) continue;
        if (c == 9 && a[3] + a[6] + i != 15) continue;
        if (c == 9 && a[1] + a[5] + i != 15) continue;
        if (c == 9 && a[7] + a[8] + i != 15) continue;
        vis[a[c] = i] = 1, dfs(c + 1), vis[i] = 0;
    }
}

int64 count(const int64* a) {
    return a[1] | a[2] << 4 | a[3] << 8 | a[4] << 12 | a[5] << 16 | a[6] << 20 |
           a[7] << 24 | a[8] << 28 | a[9] << 32;
}

void test(const int x, const int y) {
    std::swap(a[x], a[y]);
    if (!map.count(count(a))) {
        map[count(a)] = a[0], memcpy(d[++r], a, sizeof(a));
    }
    std::swap(a[x], a[y]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T, dfs(1), l = 1, r = 0;
    for (int i = 0; i < cnt; ++i) {
        memcpy(d[++r], h[i], sizeof(a)), map[count(h[i])] = 0;
    }
    while (l <= r) {
        memcpy(a, d[l++], sizeof(a)), ++a[0];
        test(1, 2), test(2, 3), test(4, 5), test(5, 6), test(7, 8), test(8, 9);
        test(1, 4), test(4, 7), test(2, 5), test(5, 8), test(3, 6), test(6, 9);
    }
    while (T--) {
        for (int i = 1; i < N; ++i) std::cin >> a[i];
        std::cout << map[count(a)] << '\n';
    }
    return 0;
}