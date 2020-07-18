#include <bits/stdc++.h>
const int M = 2000005;
const int N = 200005;
class edge {
   public:
    int s, t, v;
};
edge e[M];
int cnt, m, n, x, y;
int f[N], fi[N];
long long l, r;
int find(int);
int operator<(edge, edge);
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
inline int operator<(edge x, edge y) { return x.v < y.v; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    fi[cnt++] = 1;
    fi[cnt++] = 2;
    while (fi[cnt - 1] <= n) {
        fi[cnt] = fi[cnt - 1] + fi[cnt - 2];
        ++cnt;
    }
    for (int i = 1; i <= m; ++i) std::cin >> e[i].s >> e[i].t >> e[i].v;
    std::sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        x = find(e[i].s);
        y = find(e[i].t);
        if (x != y) {
            f[x] = y;
            l += e[i].v;
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (find(1) != find(i)) {
            std::cout << "No" << std::endl;
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = m; i; --i) {
        x = find(e[i].s);
        y = find(e[i].t);
        if (x != y) {
            f[x] = y;
            r += e[i].v;
        }
    }
    for (int i = 0; i < cnt; ++i) {
        if (l <= fi[i] && fi[i] <= r) {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    std::cout << "No" << std::endl;
    return 0;
}