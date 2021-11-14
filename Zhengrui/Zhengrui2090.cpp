#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Debug << std::endl

const int N = 300005;

int n, pa, pb, x, y, m;
int g[N];

std::vector<int> to[N], f[N];

inline bool dfs(int u, int fa) {
    bool ret = u == pb;
    std::vector<int> vec;
    for (int v : to[u]) {
        if (v == fa) continue;
        if (dfs(v, u)) {
            ret = true;
        } else {
            vec.push_back(g[v]);
        }
    }
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    if (ret) {
        f[++m].swap(vec);
    } else {
        for (int i = 0; i < vec.size(); ++i) {
            g[u] = std::max(g[u], vec[i] + i + 1);
        }
    }
    return ret;
}

inline bool check(int n) {
    int l = 1, r = m, t = 1, flag;
    while (l <= m) {
        if (t + f[l][0] > n && (--l, 1)) break;
        flag = 0;
        for (int x : f[l]) {
            if (t + x + 1 <= n && (flag = 1)) break;
            ++t;
        }
        if (flag && (++l, ++t)) continue;
        break;
    }
    t = 1;
    while (r >= 1) {
        if (t + f[r][0] > n && (++r, 1)) break;
        flag = 0;
        for (int x : f[r]) {
            if (t + x + 1 <= n && (flag = 1)) break;
            ++t;
        }
        if (flag && (--r, ++t)) continue;
        break;
    }
    return l + 1 >= r;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> pa >> pb;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    dfs(pa, pa);
    for (int i = 1; i <= m; ++i) {
        for (int j = f[i].size() - 2; j >= 0; --j) {
            f[i][j] = std::max(f[i][j + 1] + 1, f[i][j]);
        }
        f[i].push_back(-1);
    }
    int l = 1, r = n, mid;
    while (l < r) {
        mid = l + r >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l << std::endl;
    return 0;
}