#include <bits/stdc++.h>

const int C = 16;
const int N = 1 << C;

int Ans[C + 1][N];

inline std::string Out(int n) {
    std::string Ret;
    for (int i = 0; i < C; ++i) Ret += '0' + ((n >> i) & 1);
    return Ret;
}

inline int Mo(int x, int l, int r) { return x ^ ((1 << std::min(C, r + 1)) - (1 << l)); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    Ans[0][0] = 1;
    for (int i = 1; i <= C; ++i) {
        for (int j = 0; j < N; ++j) {
            if (Ans[i - 1][j]) {
                Ans[i][j] = Ans[i - 1][j];
                for (int k = 0; k < C; ++k) {
                    int x = Mo(j, k, k + i - 1);
                    if (!Ans[i - 1][x]) Ans[i][x] = i + 1;
                }
            }
        }
    }
    int T;
    std::cin >> T;
    while (T--) {
        std::string s;
        std::cin >> s;
        int n = 0, c = s.size();
        for (int i = 0; i < c; ++i) n |= s[i] - '0' << C - c + i;
        std::cout << Ans[C][n] - 1 << '\n';
    }
    return 0;
}