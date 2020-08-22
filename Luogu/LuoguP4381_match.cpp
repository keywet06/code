#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct EDGE {
    int to, next, w;
} e[2000010];
int n, head[1000001], top, in[1000001], vis[1000001], a[2000001], len,
    deep[1000001], fa[1000001], vvis[1000001], farst[1000001];
long long ws[1000001], ans[1000001], mdep[1000001], tt, max__;
void add(int u, int v, int w) {
    in[v]++;
    e[top].to = v;
    e[top].next = head[u];
    e[top].w = w;
    head[u] = top++;
}
struct _ {
    long long val;
    int id;
    _() {}
    _(long long v, int i) {
        val = v;
        id = i;
    }
    bool operator>=(_ ob) { return val >= ob.val; }
} b[2000001];
void topo() {
    queue<int> q;
    int i;
    for (i = 1; i <= n; i++) {
        if (in[i] == 1) {
            q.push(i);
        }
    }
    int x;
    while (!q.empty()) {
        x = q.front();
        q.pop();
        for (i = head[x]; ~i; i = e[i].next) {
            if (in[e[i].to] > 1) {
                in[e[i].to]--;
                if (in[e[i].to] == 1) q.push(e[i].to);
            }
        }
    }
}
void dfs(int x) {
    a[len++] = x;
    vis[x] = 1;
    int i;
    for (i = head[x]; ~i; i = e[i].next) {
        if (in[e[i].to] < 2) continue;
        if (vis[e[i].to]) continue;
        ws[len] = ws[len - 1] + e[i].w;
        dfs(e[i].to);
    }
}
void dfs1(int x) {
    farst[x] = x;
    int i;
    long long max_ = 0;
    for (i = head[x]; ~i; i = e[i].next) {
        if (e[i].to == fa[x]) continue;
        if (in[e[i].to] > 1) continue;
        fa[e[i].to] = x;
        dfs1(e[i].to);
        if (mdep[e[i].to] + e[i].w > max_) {
            max_ = mdep[e[i].to] + e[i].w;
            farst[x] = farst[e[i].to];
        }
    }
    mdep[x] = max_;
}
void dfs2(int x, long long dis) {
    if (dis > max__) max__ = dis;
    vvis[x] = 1;
    int i;
    for (i = head[x]; ~i; i = e[i].next) {
        if (in[e[i].to] >= 2) continue;
        if (vvis[e[i].to]) continue;
        dfs2(e[i].to, dis + e[i].w);
    }
    vvis[x] = 0;
}
int main() {
    memset(head, 255, sizeof(head));
    scanf("%d", &n);
    int i, u, v, w;
    for (i = 0; i < n; i++) {
        u = i + 1;
        scanf("%d%d", &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    topo();
    long long anss = 0;
    for (i = 1; i <= n; i++) {
        if (!vis[i] && (in[i] > 1)) {
            max__ = 0;
            len = 0;
            dfs(i);
            int j, cnt = 0;
            for (j = head[i]; ~j; j = e[j].next) {
                if (e[j].to == a[len - 1]) {
                    if (len != 2)
                        tt = e[j].w;
                    else {
                        cnt++;
                        if (e[j].w == ws[1]) {
                            if (cnt == 1) continue;
                        }
                        tt = e[j].w;
                    }
                    break;
                }
            }
            long long s = 0;
            for (j = 0; j < len; j++) {
                dfs1(a[j]);
                in[a[j]] = 1;
                dfs2(farst[a[j]], 0);
                in[a[j]] = 2;
                b[j] = (_){mdep[a[j]] + ws[j], j};
                b[j + len] =
                    (_){mdep[a[j]] + ws[j] + ws[len - 1] + tt, j + len};
            }
            deque<_> q;
            for (j = 1; j < len - 1; j++) {
                while (!q.empty() && (b[j] >= q.back())) q.pop_back();
                q.push_back(b[j]);
            }
            for (j = 0; j < len; j++) {
                while (!q.empty() && (b[j + len - 1] >= q.back())) q.pop_back();
                q.push_back(b[j + len - 1]);
                ans[a[j]] = q.front().val + b[j].val;
                if (q.front().id == j + 1) q.pop_front();
            }
            long long t = 0;
            for (j = 0; j < len; j++) {
                if (ans[a[j]] - (ws[j] << 1) > t) t = ans[a[j]] - (ws[j] << 1);
            }
            if (max__ > t) t = max__;
            anss += t;
        }
    }
    printf("%lld\n", anss);
    return 0;
}