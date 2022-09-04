#include <bits/stdc++.h>

using int64 = long long;

struct Node {
    int64 x, y;
};

struct Edge {
    int To;
    int64 w;
    Edge(int To = 0, int64 w = 0) { this->To = To, this->w = w; }
};

const int N = 100005;
const int N2 = N << 1;

int n, Cnt;
int Vis[N2], Sta[N2];

int64 Dis[N2], Sail[N2], Tag[N2];

Node p[N];

std::vector<int> Pwe;

std::vector<Edge> a[N2];

std::map<int64, int> Map;

void Add(int x, int y, int64 v) { a[x].emplace_back(y, v); }

void Write(int x, int k) {
    for (int i = x; i <= x + k - 1; ++i) Pwe.push_back(i);
}

int SPFA(int S) {
    std::queue<int> q;
    for (int i = 0; i <= Cnt; ++i) Dis[i] = 1000000000000000000, Vis[i] = 0, Sta[i] = 0;
    q.push(S);
    Dis[S] = 0, Vis[S] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        Vis[v] = 0;
        for (int i = 0; i < (int)a[v].size(); ++i) {
            int u = a[v][i].To;
            int64 w = a[v][i].w;
            if (Dis[v] + w < Dis[u]) {
                Dis[u] = Dis[v] + w;
                if (!Vis[u]) Vis[u] = 1, q.push(u);
                ++Sta[u];
                if (Sta[u] > Cnt) return 0;
            }
        }
    }
    return 1;
}

int Check(int Limit) {
    for (int i = 0; i <= Cnt; ++i) a[i].clear();
    for (int i = 1; i <= n; ++i) {
        int Tmp1 = p[i].x - 1, Tmp2 = p[i].y;
        Tmp1 = Map[Tmp1], Tmp2 = Map[Tmp2];
        Add(Tmp1, Tmp2, Limit);
        Add(Tmp2, Tmp1, -1);
    }
    Add(0, 1, 0), Add(1, 0, 0);
    for (int i = 1; i <= Cnt - 1; ++i) {
        Add(i, i + 1, Sail[i + 1] - Sail[i]);
        Add(i + 1, i, 0);
    }
    int ret = SPFA(0);
    return ret;
}
int bs(int l, int r) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (Check(mid)) return bs(l, mid);
    return bs(mid + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        std::vector<int64> g;
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            std::cin >> p[i].x >> p[i].y;
            g.push_back(p[i].x - 1), g.push_back(p[i].y);
        }
        std::sort(g.begin(), g.end());
        for (int i = 0; i < g.size(); ++i) {
            if (!i || g[i] != g[i - 1]) Map[g[i]] = ++Cnt, Sail[Cnt] = g[i];
        }
        int k = bs(1, n);
        Pwe.clear();
        Check(k);
        for (int i = 1; i <= n; ++i) {
            int ll = Map[p[i].x - 1] + 1, rr = Map[p[i].y];
            ++Tag[ll], --Tag[rr + 1];
        }
        int now = 0;
        for (int i = 1; i <= Cnt; ++i) {
            now = now + Tag[i];
            Write(Sail[i - 1] + 1, (Dis[i] - Dis[i - 1]) * !!now);
        }
        std::cout << k << ' ' << Pwe.size() << ' ';
        for (int i = 0; i < Pwe.size(); ++i) std::cout << Pwe[i] << ' ';
        std::cout << '\n';
        for (int i = 0; i <= Cnt + 1; ++i) Tag[i] = Sail[i] = 0;
        Map.clear();
        for (int i = 1; i <= n; ++i) p[i].x = p[i].y = 0;
        Cnt = 0;
    }
    return 0;
}