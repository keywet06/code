#include <bits/stdc++.h>
const int N = 10005;
int n, Q, l, r, k;
int a[N], dp[N];
const int P = 200000005;
const int N = 200005;
const int X = 20000005;
class node {
   public:
    int ls, rs, size;
};
int n, k, x, y, z, cnt;
int fa[N], deep[N], root[N];
node p[X];
std::vector<std::pair<int, int> > to[N];
inline void insert(int u, int l, int r, int x) {
    ++size[u];
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) {
        p[++cnt] = p[p[u].ls];
        insert(p[u].ls = cnt, l, mid, x);
    } else {
        p[++cnt] = p[p[u].rs];
        insert(p[u].rs = cnt, mid + 1, r, x);
    }
}
inline void merge(int u, int u1, int u2, int l, int r) {

}
inline int dfs(int u, int f) {
    fa[u] = f;
    for (auto v : to[u]) {
        if (v.first == f) continue;
        deep[v.first] = deep[u] + v.seconed;
        dfs(v.first, u);
    }
}
int main() {
    std::cin >> n >> Q;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    while (Q--) {
        std::cin >> l >> r >> k;

    }
    return 0;
}