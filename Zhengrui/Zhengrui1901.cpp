#include <bits/stdc++.h>

const int INF = 1000000000;
const int N = 500005;
const int M = N << 1;

class node {
   private:
    int max, rmax;

   public:
    node() { max = rmax = 0; }
    void insert(int x) {
        if (x > max) {
            rmax = max, max = x;
        } else if (x > rmax) {
            rmax = x;
        }
    }
    void insert(node x) { insert(x.val()), insert(x.val2()); }
    int val() { return max; }
    int val2() { return rmax; }
};

int n, cnt, x, y;
int a[N], dp[N], fa[N];

std::vector<int> tos[N], to[N];

inline void insert(int x, int y) { tos[x].push_back(y); }

inline void addedge(int x, int y) { insert(x, y), insert(y, x); }

inline void dfs(int u, int f) {
    int max = 0, rmax = 0;
    for (int v : tos[u]) {
        if (v == f) continue;
        dfs(v, u), to[u].push_back(v);
        if (x > max) {
            rmax = max, max = x;
        } else if (x > rmax) {
            rmax = x;
        }
    }
    dp[u] = std::max(a[u], rmax);
}

inline void dfs2(int u, int f) {
    int n = to[u].size();
    if (!n) return;
    node x;
    node l[n];
    x.insert(a[u]), x.insert(fa[u]);
    l[n - 1].insert(dp[to[u][n - 1]]);
    for (int i = n - 2; ~i; --i) {
        (l[i] = l[i + 1]).insert(dp[to[u][i]]);
    }
    for (int i = 0; i < n - 1; ++i) {
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        addedge(x, y);
    }
    dfs(1, 1);
    return 0;
}