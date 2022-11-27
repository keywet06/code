#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;
const int INF = 1e9;

int n, Cnt, W[N], h[N];

int64 Ans;

std::map<int, int64> Nap[N];
std::map<int, int64>::iterator It;

struct Edge {
    int v, p, w;
} e[N];

inline void Insert(int U, int V, int W) {
    e[++Cnt].v = V;
    e[Cnt].p = h[U];
    e[h[U] = Cnt].w = W;
}

inline void Merge(std::map<int, int64>& A, std::map<int, int64>& B, int z) {
    for (int t; !A.empty() && (t = (*A.rbegin()).first) > z;) A[z] += (*A.rbegin()).second, A.erase(t);
    for (int t; !B.empty() && (t = (*B.rbegin()).first) > z;) B[z] += (*B.rbegin()).second, B.erase(t);
    std::vector<std::pair<int, int64> > Vec;
    int64 Cs = 0;
    for (It = B.begin(); It != B.end(); ++It) Vec.push_back(*It), Ans += (*It).first * (*It).second, Cs += (*It).second;
    Vec.emplace_back(z, 0);
    for (int i = Vec.size(); --i;) Vec[i].second = Vec[i - 1].second;
    Vec[0].second = -Cs;
    for (int i = 0, sz = Vec.size(), lst = 0; i < sz; lst = Vec[i++].first) A[z - lst] += Vec[i].second;
    for (int64 t, v = 0; !A.empty();) {
        t = (*A.rbegin()).first, v += (*A.rbegin()).second, A.erase(t);
        if (v > 0 && (A[t] = v, true)) break;
    }
}

void Dfs(int nw, int fa) {
    Nap[nw][INF] = W[nw];
    for (int i = h[nw]; i; i = e[i].p) {
        if (e[i].v ^ fa) Dfs(e[i].v, nw), Merge(Nap[nw], Nap[e[i].v], e[i].w);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> W[i];
    for (int i = 1, u, v, w; i < n; ++i) std::cin >> u >> v >> w, Insert(u, v, w), Insert(v, u, w);
    Dfs(1, 0);
    for (It = Nap[1].begin(); It != Nap[1].end(); ++It) Ans += (*It).first * (*It).second;
    std::cout << Ans << '\n';
    return 0;
}