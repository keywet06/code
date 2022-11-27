#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;

int m;
int y[N];

int64 n, Ans;
int64 x[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) std::cin >> x[i] >> y[i];
    if (m == 0) {
        Ans = n & 1;
    } else {
        Ans = (x[1] - 1) ^ (n - x[m]);
        for (int i = 1; i < m; ++i) Ans ^= x[i] != x[i + 1] && y[i] == y[i + 1];
    }
    std::cout << (Ans ? "Takahashi" : "Aoki") << '\n';
    return 0;
}