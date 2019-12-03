#include <bits/stdc++.h>
const int A_MIN = 1;
const int A_MAX = 1e9;
const int C = 4000005;
const int N = 100005;
class Node {
   public:
    int size, lson, rson;
};
int n, m, cnt, x, y, ls1, ls2, ls3;
int tree[N];
long long ans;
Node node[C];
void update(int, int, int = A_MIN, int = A_MAX);
int query(int, int, int, int = A_MIN, int = A_MAX);
int Main();
inline void update(int v, int x, int l, int r) {
    ++node[v].size;
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) {
        node[++cnt] = node[node[v].lson];
        update(node[v].lson = cnt, x, l, mid);
    } else {
        node[++cnt] = node[node[v].rson];
        update(node[v].rson = cnt, x, mid + 1, r);
    }
}
inline int query(int v1, int v2, int k, int l, int r) {
    if (l == r) {
        return l;
    }
    int mid = l + r >> 1,
      tmp = node[node[v1].rson].size - node[node[v2].rson].size;
    return k <= tmp ? query(node[v1].rson, node[v2].rson, k, mid + 1, r) :
      query(node[v1].lson, node[v2].lson, k - tmp, l, mid);
}
inline int Main() {
    tree[0] = cnt = 1;
    node[1] = node[0];
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        tree[i] = ++cnt;
        node[tree[i]] = node[tree[i - 1]];
        update(tree[i], x);
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        if (x + 1 > y) {
            std::cout << -1 << std::endl;
            continue;
        }
        ans = -1;
        ls1 = query(tree[y], tree[x - 1], 1);
        ls2 = query(tree[y], tree[x - 1], 2);
        for (int i = 3; i <= y - x + 1; ++i) {
            ls3 = query(tree[y], tree[x - 1], i);
            if (ls2 + ls3 > ls1) {
                ans = 0ll + ls1 + ls2 + ls3;
                break;
            }
            ls1 = ls2;
            ls2 = ls3;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    while (std::cin >> n >> m) {
        Main();
    }
    return 0;
}