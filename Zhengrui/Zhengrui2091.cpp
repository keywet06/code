#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

const int N = 200005;

int n, m, k, u, v, w, px;
int a[N], p[N], q[N], f[N], c[N], s[N], d[N], r[N], ans[N];

std::vector<int> to[N], ban[N];

std::unordered_map<int, int> kind[N];

std::multiset<int> set;

int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }

void erase(int u) { set.erase(set.find(d[u])); }

void merge(int u, int v) {
    s[u] += s[v], f[v] = u;
    for (auto &p : kind[v]) {
        int &x = kind[u][p.first];
        d[u] -= x && !(x % k), x += p.second, d[u] += !(x % k);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> u, kind[i][u] = 1, d[i] = k == 1;
    while (m--) {
        std::cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    std::cin >> w;
    for (int i = 1; i <= w; ++i) {
        std::cin >> c[i] >> u, ban[i].resize(u);
        for (int &x : ban[i]) std::cin >> x;
    }
    for (int i = 1; i <= n; ++i) f[i] = p[i] = i;
    for (int i = 1; i <= w; ++i) q[i] = i;
    std::sort(p + 1, p + n + 1, [](int x, int y) { return a[x] < a[y]; });
    std::sort(q + 1, q + w + 1, [](int x, int y) { return c[x] < c[y]; });
    px = 1;
    for (int i = 1; i <= w; ++i) {
        while (px <= n && a[p[px]] <= c[q[i]]) {
            s[v = u = p[px++]] = 1;
            for (int x : to[u]) {
                if (kind[find(x)].size() > kind[v].size()) v = find(x);
            }
            if (u != v) erase(v), merge(v, u);
            for (int x : to[u]) {
                if (!s[x] || find(x) == v) continue;
                erase(find(x)), merge(v, find(x));
            }
            set.insert(d[v]);
        }
        for (int x : ban[q[i]]) {
            if (!s[x] || r[find(x)]) continue;
            r[find(x)] = 1, erase(find(x));
        }
        auto it = set.end();
        ans[q[i]] = set.empty() ? 0 : *--it;
        for (int x : ban[q[i]]) {
            if (!r[find(x)]) continue;
            r[find(x)] = 0, set.insert(d[find(x)]);
        }
    }
    for (int i = 1; i <= w; ++i) std::cout << ans[i] << '\n';
    return 0;
}