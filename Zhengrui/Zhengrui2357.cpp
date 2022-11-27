#include <bits/stdc++.h>

const int C = 125;
const int D = 701;
const int N = 100005;

using Bit = std::bitset<C>;

int PCnt, p[C], Ls[D];

int n;
int Last[N], Next[N];

Bit Sum[N];

inline bool Gcd(int i, int j) { return (Sum[i] & Sum[j]).count(); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    memset(Ls, 255, sizeof(Ls));
    for (int i = 2; i < D; ++i) {
        if (Ls[i] == -1) p[Ls[i] = PCnt++] = i;
        for (int j = 0; j < PCnt && p[j] * i < D; ++j) {
            Ls[p[j] * i] = j;
            if (!(i % p[j])) break;
        }
    }
    std::cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        std::cin >> x;
        while (Ls[x] != -1) Sum[i][Ls[x]] = 1, x /= p[Ls[x]];
        Last[i] = i - 1, Next[i] = i < n ? i + 1 : 0;
    }
    std::queue<int> Que;
    for (int i = 1; i < n; ++i) Que.push(i);
    int Cnt = 0;
    while (!Que.empty()) {
        int u = Que.front();
        Que.pop();
        if (!u || !Next[u] || !Gcd(u, Next[u])) continue;
        int v = Next[u];
        ++Cnt, Sum[u] |= Sum[v];
        if (Next[u] = Next[v]) Last[Next[u]] = u, Next[v] = 0;
        Que.push(u), Que.push(Last[u]);
    }
    std::cout << (Cnt == n - 1 ? "Yes" : "No") << '\n';
    return 0;
}