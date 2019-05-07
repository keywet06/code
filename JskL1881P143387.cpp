#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
const int MAX_N = 1000;
const int MAX_M = 10000;
const int inf = 0x3f3f3f3f;
struct edge {
    int v, c, w, next;
} e[MAX_M];
int p[MAX_N], s, t, eid;
void init() {
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int u, int v, int c, int w) {
    e[eid].v = v;
    e[eid].c = c;
    e[eid].w = w;
    e[eid].next = p[u];
    p[u] = eid++;
}
void addedge(int u, int v, int c, int w) {
    insert(u, v, c, w);
    insert(v, u, 0, -w);
}
void addedge2(int u, int v, int c, int w) {
    addedge(u, v, c, w);
    addedge(v, u, c, -w);
}
bool vis[MAX_N];
int d[MAX_N];
int pre[MAX_N];
bool spfa() {
    memset(vis, 0, sizeof(vis));
    memset(d, 0x3f, sizeof(d));
    memset(pre, -1, sizeof(pre));
    d[s] = 0;
    vis[s] = true;
    queue<int> q;
    q.push(s);
	while (!q.empty()) {
	    int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = p[u]; ~i; i = e[i].next) {
            if (e[i].c) {
                int v = e[i].v;
                if (d[u] + e[i].w < d[v]) {
                    d[v] = d[u] + e[i].w;
                    pre[v] = i;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
	}
    return ~pre[t];
}
int costflow() {
    int ret = 0;
    while (spfa()) {
        int flow = inf;
        for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
            flow = min(e[pre[i]].c, flow);
        }
        for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
            e[pre[i]].c -= flow;
            e[pre[i] ^ 1].c += flow;
            ret += e[pre[i]].w * flow;
        }
    }
    return ret;
}
int main() {
    // freopen("road.in", "r", stdin);
    // freopen("road.out", "w", stdout);
	int n, m;
    init();
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, c, w;
        cin >> u >> v >> w >> c;
        if (c) {
            addedge2(u, v, w, 1);
        } else {
            addedge(u, v, w, 1);
        }
        printf("Debug: i = %d is OK!", i);
    }
    s = 0;
    t = n - 1;
    cout << costflow() << endl;
    return 0;
}