#include <bits/stdc++.h>
const int N = 200005;
int cnt, m, c, k;
int son[N][2], fa[N], plus[N], max[N], min[N], opt[N], val[N], lsh[N], p[N],
  to[N];
void build(int v, int l, int r);
void pushup(int v);
void pushdown(int v);
void insert(int v, int x, int l, int r, int lm, int rm);
inline void build(int v, int l, int r) {
    if (l == r) {
        to[l] = v;
        p[v] = l;
        return;
    }
    int mid = l + r >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
}
inline void pushup(int v) {
    max[v] = max[v << 1 | 1] ? max[v << 1 | 1] : max[v << 1];
    min[v] = min[v << 1] ? min[v << 1] : min[v << 1 | 1];
}
inline void pushdown(int v) {
    plus[v << 1] += plus[v];
    plus[v << 1 | 1] += plus[v];
    plus[v] = 0;
}
inline void insert(int v, int x, int l, int r, int lm, int rm) {
    if (l == r) {
        fa[l] = std::max(lm, rm);
        min[v] = max[v] = plus[v] = l;
        son[fa[l]][lm < rm] = l;
        return;
    }
    int mid = l + r >> 1;
    pushdown(v);
    if (x <= mid) {
        insert(v << 1, x, l, mid, lm, min[son[v][1]] ? min[son[v][1]] : rm);
    } else {
        insert(v << 1 | 1, x, mid + 1, r, max[son[v][0]] ? max[son[v][0]] : lm, 
          rm);
    }
    pushup(v);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> opt[i];
        if (opt[i] == 1) {
            std::cin >> val[i];
            lsh[cnt++] = i;
        }
    }
    std::sort(lsh, lsh + cnt, [](int x, int y) { return val[x] < val[y]; });
    for (int i = 0; i < cnt; ++i) {
        val[lsh[i]] = i + 1;
    }
    build(1, 1, cnt);
    for (int i = 1; i <= m; ++i) {
        if (opt[i] == 1) {
            insert(1, val[i], 1, cnt, 0, 0);
        } else if (opt[i] == 2) {

        }
    }
    return 0;
}