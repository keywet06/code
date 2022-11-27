#include <bits/stdc++.h>

const int N = 500005;

int n, m;
int Fir[N], Las[N], S[N], T[N], Fen[N];

inline void Add(int u, int v) {
    while (u < N) Fen[u] = std::max(Fen[u], v), u += u & -u;
}

inline int Sum(int u) {
    int Ans = 0;
    while (u) Ans = std::max(Ans, Fen[u]), u &= u - 1;
    return Ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> S[i];
    for (int i = 1; i <= m; ++i) std::cin >> T[i], Fir[T[i]] = Fir[T[i]] ? Fir[T[i]] : i, Las[T[i]] = i;
    int No = 0;
    for (int i = 1; i <= n; ++i) {
        if (Fir[S[i]]) {
            Add(m - Fir[S[i]] + 1, Sum(m - Las[S[i]] + 1) + 1);
        } else {
            ++No;
        }
    }
    std::cout << No + Sum(m) << '\n';
    return 0;
}