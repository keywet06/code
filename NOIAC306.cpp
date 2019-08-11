#include <bits/stdc++.h>
const int N = 400005;
class node {
    public:
        node(int);
        int v;
};
int ans, cnt, m, n, tmp;
int a[N], next[N], last[N], vis[N];
int operator < (node, node);
std::priority_queue<node> pq;
int main() {
    scanf("%d %d", &n, &m);
    if (m * 2 > n) {
        puts("Error");
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        next[i] = i + 1;
        last[i] = i - 1;
        pq.push((node)(i));
    }
    last[1] = n;
    next[n] = 1;
    cnt = n;
    for (int i = 1; i <= m; ++i) {
        while (vis[tmp = pq.top().v]) {
            pq.pop();
        }
        pq.pop();
        ans += a[tmp];
        vis[tmp] = 1;
        vis[last[tmp]] = 1;
        vis[next[tmp]] = 1;
        a[++cnt] = a[last[tmp]] + a[next[tmp]] - a[tmp];
        last[cnt] = last[last[tmp]];
        next[last[cnt]] = cnt;
        next[cnt] = next[next[tmp]];
        last[next[cnt]] = cnt;
        pq.push((node)(cnt));
    }
    printf("%d\n", ans);
    return 0;
}
inline node::node(int x) {
    this->v = x;
}
inline int operator < (node x, node y) {
    return a[x.v] < a[y.v];
}