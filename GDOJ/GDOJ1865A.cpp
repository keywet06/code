#include <bits/stdc++.h>

using int64 = long long;

using Pair = std::pair<int, int>;

const int N = 200005;

int n, m, CycTop;
int Dep[N];

int64 Ans, sx, sy;

Pair DfsP[N];

std::vector<Pair> So, Cyc[N], Ct[N];

std::vector<std::pair<int, Pair> > To[N];

inline void Dfs(int u, int Fa) {
    Dep[u] = Dep[Fa] + 1;
    int v;
    for (auto p : To[u]) {
        if ((v = p.first) == Fa) continue;
        DfsP[Dep[u]] = p.second;
        if (Dep[v]) {
            if (Dep[v] > Dep[u]) continue;
            ++CycTop;
            for (int i = Dep[v]; i <= Dep[u]; ++i) Cyc[CycTop].push_back(DfsP[i]);
        } else {
            Dfs(v, u);
        }
    }
}

inline bool Check(Pair a, Pair b, Pair c) {
    return b.second * int64(a.first - b.first) - int64(a.second - b.second) * (b.first - c.first) >=
           c.second * int64(a.first - b.first);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1, u, v, x, y; i <= m; ++i) {
        std::cin >> u >> v >> x >> y, sx += x, sy += y;
        To[u].emplace_back(v, Pair(x, y));
        To[v].emplace_back(u, Pair(x, y));
    }
    Dfs(1, 1);
    for (int i = 1; i <= CycTop; ++i) {
        std::vector<Pair> &Y = Cyc[i], &T = Ct[i];
        std::sort(Y.begin(), Y.end());
        for (auto p : Y) {
            while (T.size() && p.second >= T.front().second) T.pop_back();
            while (T.size() > 1 && Check(T[T.size() - 2], T.back(), p)) T.pop_back();
            T.push_back(p);
        }
        sx -= T.front().first, sy -= T.front().second;
        for (int i = 1; i < T.size(); ++i) So.emplace_back(T[i].first - T[i - 1].first, T[i - 1].second - T[i].second);
    }
    std::sort(So.begin(), So.end(), [](Pair a, Pair b) { return a.second * b.first < a.first * b.second; });
    Ans = sx * sy;
    for (auto p : So) Ans = std::min(Ans, (sx -= p.first) * (sy += p.second));
    std::cout << Ans << std::endl;
    return 0;
}