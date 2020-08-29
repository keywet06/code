#include <bits/stdc++.h>
const int N = 55;
const int M = 2505;
int en = 1, mc, mf, h[N], dis[N], n, k;
bool v[N];
struct edge {
    int n, v, f, w;
} e[M << 1];
struct node {
    int fa, id;
} pre[N];
void add(int x, int y, int f, int w) {
    e[++en] = (edge){h[x], y, f, w};
    h[x] = en;
}
bool spfa(int s, int t) {
    memset(v, 0, sizeof v);
    memset(pre, 0, sizeof pre);
    memset(dis, 0x3f, sizeof dis);
    std::queue<int> q;
    q.push(s);
    v[s] = 1;
    dis[s] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = h[x]; i; i = e[i].n) {
            int y = e[i].v;
            if (e[i].f && dis[x] + e[i].w < dis[y]) {
                dis[y] = dis[x] + e[i].w;
                pre[y] = (node){x, i};
                if (!v[y]) {
                    v[y] = 1;
                    q.push(y);
                }
            }
        }
        v[x] = 0;
    }
    return dis[t] ^ 0x3f3f3f3f;
}
void flow(int s, int t) {
    while (spfa(s, t)) {
        int flow = INT_MAX;
        for (int i = t; i ^ s; i = pre[i].fa) {
            flow = std::min(flow, e[pre[i].id].f);
        }
        for (int i = t; i ^ s; i = pre[i].fa) {
            e[pre[i].id].f -= flow;
            e[pre[i].id ^ 1].f += flow;
        }
        mf += flow;
        mc += flow * dis[t];
    }
}
void exadd(int x, int y, int f, int w) {
    add(x, y, f, w);
    add(y, x, 0, -w);
}
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, x; j <= n; j++) {
            std::cin >> x;
            if (x) exadd(i, j, x, 0);
        }
    }
    exadd(0, 1, INT_MAX, 0);
    exadd(n, n + 1, INT_MAX, 0);
    flow(0, n + 1);
    while (mc < k) {
        for (int i = 2; i <= en; i += 2)
            if (!e[i].f) {
                e[i].f++;
                e[i].w = 1;
            }
        int s, t;
        spfa(s = 0, t = n + 1);
        int flow = INT_MAX;
        for (int i = t; i ^ s; i = pre[i].fa) {
            flow = std::min(flow, e[pre[i].id].f);
        }
        for (int i = t; i ^ s; i = pre[i].fa) {
            e[pre[i].id].f -= flow;
            e[pre[i].id ^ 1].f += flow;
        }
        if (!flow) break;
        if (mc + flow * dis[t] > k) {
            mf += (k - mc) / dis[t];
            break;
        }
        mf += flow;
        mc += flow * dis[t];
    }
    std::cout << mf << std::endl;
    return 0;
}