#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

const int N = 500005;
const int M = 1048576;

int nn, n, m, Ans;
int a[N], Opt[M], Min[M], Add[M];

inline void AddU(int u, int s, bool c) {
    Min[u] += s, Add[u] += s;
    if (c) {
        Ans -= bool(Min[u] - s), Ans += bool(Min[u]);
        Opt[u] = Min[u] <= 1 ? 0 : Min[u] & 1 ? -1 : 1;
    } else {
        Opt[u] = (s & 1 ? -Opt[u] : Opt[u]), Opt[u] = Min[u] > 1 ? Opt[u] : 0;
    }
}

inline void PushDown(int u, int l, int m, int r) {
    if (Add[u]) AddU(u << 1, Add[u], l == m), AddU(u << 1 | 1, Add[u], m + 1 == r), Add[u] = 0;
}

inline void PushUp(int u) {
    Min[u] = std::min(Min[u << 1], Min[u << 1 | 1]);
    Opt[u] = Opt[u << 1] == Opt[u << 1 | 1] ? Opt[u << 1] : 0;
}

inline int Find(int u, int l, int r, int x, int o) {
    if (Opt[u] || l == r) return Opt[u] == o ? r : std::max(x, l) - 1;
    int Mid = l + r >> 1, Ret = (PushDown(u, l, Mid, r), x <= Mid ? Find(u << 1, l, Mid, x, o) : Mid);
    return Ret < Mid ? Ret : Find(u << 1 | 1, Mid + 1, r, x, o);
}

inline void AddS(int u, int l, int r, int x, int y, int v) {
    if (l >= x && r <= y) return AddU(u, v, l == r);
    int Mid = l + r >> 1;
    PushDown(u, l, Mid, r);
    if (x <= Mid) AddS(u << 1, l, Mid, x, y, v);
    if (y > Mid) AddS(u << 1 | 1, Mid + 1, r, x, y, v);
    PushUp(u);
}

inline void AddP(int u) {
    int x = Find(1, 1, n, u, 1);
    if (u <= x) AddS(1, 1, n, u, x, 1);
    AddS(1, 1, n, x + 1, x + 1, 1);
}

inline void SubP(int u) {
    int x = Find(1, 1, n, u, -1);
    if (u <= x) AddS(1, 1, n, u, x, -1);
    AddS(1, 1, n, x + 1, x + 1, -1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> nn >> m, n = N + 50;
    for (int i = 1; i <= nn; ++i) std::cin >> a[i], AddP(a[i]);
    while (m--) {
        int o;
        std::cin >> o;
        if (o == 1) {
            int i, x;
            std::cin >> i >> x, SubP(a[i]), AddP(a[i] = x);
        } else {
            std::cout << Ans << '\n';
        }
    }
    return 0;
}