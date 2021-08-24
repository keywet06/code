#include <bits/stdc++.h>

using int64 = long long;

const int C = 22;
const int N = 100010;

int n, m, tot;
int64 rum, ugn;

struct edge {
    int to, next, w;
} e[N];

int head[N], rs[N], tpn[N], tag[N], army[N];
int f[N][C];

int64 rmrf[N], dis[N][C];

void add(int x, int y, int z) {
    e[++tot].to = y, e[tot].w = z;
    e[tot].next = head[x], head[x] = tot;
}

void dfs(int x, int hf, int64 len) {
    f[x][0] = hf, dis[x][0] = len;
    for (int i = 1; i <= 17; i++) {
        f[x][i] = f[f[x][i - 1]][i - 1];
        dis[x][i] = dis[x][i - 1] + dis[f[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = e[i].next) {
        if (e[i].to != hf) dfs(e[i].to, x, e[i].w);
    }
}

struct node {
    int id;
    int64 st;
} ram[N], gap[N];

int gety(int x, int hf) {
    bool fg = 1;
    bool flag = 0;
    if (rs[x]) return 1;
    for (int i = head[x]; i; i = e[i].next) {
        if (e[i].to == hf) continue;
        flag = 1;
        if (gety(e[i].to, x)) continue;
        fg = 0;
        if (x != 1) return 0;
        gap[++ugn].id = e[i].to, gap[ugn].st = e[i].w;
    }
    return flag ? fg : 0;
}

bool cmp(node x, node y) { return x.st > y.st; }
bool check(int64 lim) {
    rum = ugn = 0;
    for (int i = 1; i <= n; i++) rs[i] = tpn[i] = 0;
    for (int i = 1; i <= m; i++) tag[i] = 0;
    int num, x;
    for (int i = 1; i <= m; i++) {
        x = army[i], num = 0;
        for (int j = 17; j >= 0; j--) {
            if (f[x][j] > 1 && num + dis[x][j] <= lim) {
                num += dis[x][j], x = f[x][j];
            }
        }
        if (f[x][0] == 1 && lim - num - dis[x][0] >= 0) {
            ram[++rum].id = i;
            ram[rum].st = lim - num - dis[x][0];
            if (!tpn[x] || rmrf[x] > ram[rum].st) {
                tpn[x] = i, rmrf[x] = ram[rum].st;
            }
        } else {
            rs[x] = 1;
        }
    }
    if (gety(1, 0)) return 1;
    std::sort(ram + 1, ram + rum + 1, cmp);
    std::sort(gap + 1, gap + ugn + 1, cmp);
    int now = tag[0] = 1;
    for (int i = 1; i <= ugn; i++) {
        if (!tag[tpn[gap[i].id]]) {
            tag[tpn[gap[i].id]] = 1;
            continue;
        }
        while (now <= rum && (tag[ram[now].id] || ram[now].st < gap[i].st)) {
            now++;
        }
        if (now > rum) return 0;
        tag[ram[now].id] = 1;
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    dfs(1, 0, 0);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%d", &army[i]);
    int l = 1, r = 500000, mid;
    int64 ans = 0;
    while (l <= r) check(mid = l + r >> 1) ? r = (ans = mid) - 1 : l = mid + 1;
    std::cout << ans << std::endl;
    return 0;
}