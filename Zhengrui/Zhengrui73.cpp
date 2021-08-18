#include <bits/stdc++.h>

using int64 = long long;

const int C = 3;
const int N = 9;
const int64 R = 804434861;
const int64 P = 998244353;

bool f[N];
bool v[C][C];

int T, ans, cns;
int b[N][N];

std::string s;

inline void dfs(int p) {
    if (p >= N) return void(++ans);
    for (int i = 0; i < N; ++i) {
        if (f[i] || v[p / C][i / C] || !b[p][i]) continue;
        v[p / C][i / C] = f[i] = 1, dfs(p + 1), v[p / C][i / C] = f[i] = 0;
    }
}

int main() {
    std::cin >> T;
    while (T--) {
        for (int i = 0; i < N; ++i) {
            std::cin >> s;
            for (int j = 0; j < N; ++j) b[i][j] = s[j] == '1';
        }
        ans = 0, dfs(0), std::cout << ans * R % P << std::endl;
    }
    return 0;
}