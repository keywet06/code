#include <bits/stdc++.h>

const int P = 1000000007;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? x += P : x; }

const int N = 105;
const int M = 1005;

int n;
int h[N];
int f[N][M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> h[i];
    int R = n & 1 ? h[1] : 0;
    for (int i = 2; i <= n; ++i) R = std::min(R, h[i]);
    f[1][0] = 1;
    int Ans = 0;
    for (int c = 0; c <= R; ++c) {
        for (int i = 1, I = i + 1; i < n; ++i, ++I) {
            memset(f[I], 0, (h[I] - c + 1) * sizeof(int));
            for (int j = 0; j <= h[i] - c; ++j) {
                Adds(f[I][std::min(h[i] - j, h[I]) - c], f[i][j]);
            }
            for (int j = h[I] - c - 1; j >= 0; --j) Adds(f[I][j], f[I][j + 1]);
        }
        for (int j = 0; j <= h[n] - c; ++j) Adds(Ans, f[n][j]);
    }
    std::cout << Ans << std::endl;
    return 0;
}