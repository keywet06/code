#include <bits/stdc++.h>
const int A_MIN = 0;
const int A_MAX = 1000005;
const int C = 50000005;
const int N = 1000005;
class Node {
   public:
    int size, lson, rson;
};
int T, n, m, x, y, z, k, cnt, now, rank, l, r, mid, ans;
int tree[N];
Node node[C];
void update(int, int, int = A_MIN, int = A_MAX);
int query(int, int, int, int, int = A_MIN, int = A_MAX);
int Main();
inline void update(int v, int x, int l, int r) {
    ++node[v].size;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) {
        node[++cnt] = node[node[v].lson];
        update(node[v].lson = cnt, x, l, mid);
    } else {
        node[++cnt] = node[node[v].rson];
        update(node[v].rson = cnt, x, mid + 1, r);
    }
}
inline int query(int v1, int v2, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return node[v1].size - node[v2].size;
    }
    int mid = (l + r) / 2;
    return (x <= mid ? query(node[v1].lson, node[v2].lson, x, y, l, mid) : 0) +
      (y > mid ? query(node[v1].rson, node[v2].rson, x, y, mid + 1, r) : 0);
}
inline int Main() {
    std::cin >> n >> m;
    cnt = tree[0] = 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        node[tree[i] = ++cnt] = node[tree[i - 1]];
        update(tree[i], x);
    }
    ans = 0;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z >> k;
        x ^= ans;
        y ^= ans;
        z ^= ans;
        k ^= ans;
        l = 0;
        r = A_MAX;
        while (l < r) {
            mid = (l + r) / 2;
            if (query(tree[y], tree[x - 1],
              std::max(z - mid, A_MIN), std::min(z + mid, A_MAX)) < k) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        std::cout << (ans = l) << std::endl;
    }
    return 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        Main();
    }
    return 0;
}