#include <bits/stdc++.h>
const int M = 200005;
const int N = 5005;
class edge {
    public:
        int s, t, v;
};
edge e[M];
int cnt, m, n, x, y;
int f[N];
long long ans;
int find(int);
int operator < (edge, edge);
inline int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
inline int operator < (edge x, edge y) {
    return x.v < y.v;
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &e[i].s, &e[i].t, &e[i].v);
    }
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        x = find(e[i].s);
        y = find(e[i].t);
        if (x != y) {
            f[x] = y;
            ans += e[i].v;
        }
    }
    printf("%lld\n", ans);
    return 0;
}