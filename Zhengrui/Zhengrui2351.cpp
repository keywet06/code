#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int M = 25;

int n, m, q, x, y, z, t, inf = 1e9;
int Dep[N], Time[N << 1], Vis[N];
int f[N][M];

std::vector<std::pair<int, int> > v[N];

struct Node {
    int l[2], r[2], f[2][2];
    friend Node operator+(Node a, Node b) {
        if (!a.l[0]) return b;
        Node c = {a.l[0], a.l[1], b.r[0], b.r[1], -inf, -inf, -inf, -inf};
#define For_(i) for (int i = 0; i < 2; ++i)
        For_(i) For_(j) For_(k) For_(l) c.f[i][l] = std::max(c.f[i][l], a.f[i][j] + b.f[k][l] + (a.r[j] != b.l[k]));
#undef For_
        return c;
    }
} g[N][M], a, b, Ans;

void Dfs(int x, int fa) {
    Vis[x] = 1, Dep[x] = Dep[fa] + 1;
    int Num = 0, c1 = 0, c2 = 0, y;
    ++t;
    for (auto p : v[x]) {
        int y = p.first, z = p.second;
        if (y == fa && Time[z] ^ t) Time[z] = t, ++Num == 1 ? c1 = z : c2 = z;
    }
    if (Num > 2) Num = 1, c1 = x + m;
    g[x][0] = Num == 1 ? Node{c1, 0, c1, 0, 0, -inf, -inf, -inf} : Node{c1, c2, c1, c2, 0, -inf, -inf, 0};
    for (int i = 0; i <= 19; ++i) f[x][i + 1] = f[f[x][i]][i], g[x][i + 1] = g[x][i] + g[f[x][i]][i];
    for (auto p : v[x]) {
        if (!Vis[y = p.first]) f[y][0] = x, Dfs(y, x);
    }
}

int Lca(int x, int y) {
    if (Dep[x] < Dep[y]) std::swap(x, y);
    for (int i = 20; i >= 0; --i) {
        if (Dep[f[x][i]] >= Dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 20; i >= 0; --i) {
        if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}

Node get(int x, int y) {
    Node Ans = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 20; i >= 0; --i) {
        if (Dep[f[x][i]] >= Dep[y]) Ans = Ans + g[x][i], x = f[x][i];
    }
    return Ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z;
        v[x].emplace_back(y, z), v[y].emplace_back(x, z);
    }
    Dfs(1, 0), std::cin >> q;
    while (q--) {
        std::cin >> x >> y;
        if (x == y && (std::cout << "0\n", true)) continue;
        z = Lca(x, y), a = get(x, z), b = get(y, z);
        std::swap(b.l, b.r), std::swap(b.f[0][1], b.f[1][0]);
        Ans = x ^ z && y ^ z ? a + b : (x == z ? b : a);
        std::cout << std::max({Ans.f[0][0], Ans.f[0][1], Ans.f[1][0], Ans.f[1][1]}) << '\n';
    }
    return 0;
}