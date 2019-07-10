#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int C = 1000;
const int N = 50005;
const int M = 1000005;
const int move[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int n, m, S, T, cnt, flag1, flag2, sum;
int cost[M], flews[M], to[M], next[M];
int min[N], dis[N], head[N], vis[N], from[N];
int map[C][C], val[C][C];
int id[C][C][3];
int read();
void add(int, int, int, int);
int SPFA();
int find();
int Dinic();
int main() {
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    n = read();
    m = read();
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            map[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            map[i][j] = read();
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            val[i][j] = read();
            if (!map[i][j]) {
                sum += val[i][j];
            }
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!map[i][j]) {
                for (int k = 0; k < 3; k++) {
                    id[i][j][k] = ++flag2;
                }
            }
        }
    }
    S = 0;
    T = ++flag2;
    flag2 = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!map[i][j]) {
                if ((i + j) & 1) {
                    flag1 += 2;
                    add(S, id[i][j][0], 2, 0);
                    add(id[i][j][0], id[i][j][1], 1, 0);
                    add(id[i][j][0], id[i][j][2], 1, 0);
                    add(id[i][j][0], id[i][j][1], 1, -val[i][j]);
                    add(id[i][j][0], id[i][j][2], 1, -val[i][j]);
                } else {
                    flag2 += 2;
                    add(id[i][j][0], T, 2, 0);
                    add(id[i][j][1], id[i][j][0], 1, 0);
                    add(id[i][j][2], id[i][j][0], 1, 0);
                    add(id[i][j][1], id[i][j][0], 1, -val[i][j]);
                    add(id[i][j][2], id[i][j][0], 1, -val[i][j]);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!map[i][j] && ((i + j) & 1)) {
                for (int k = 0; k < 4; k++) {
                    int x = i + move[k][0], y = j + move[k][1];
                    if (!map[x][y]) {
                        if (k < 2) {
                            add(id[i][j][1], id[x][y][1], 1, 0);
                        } else {
                            add(id[i][j][2], id[x][y][2], 1, 0);
                        }
                    }
                }
            }
        }
    }
    if (flag1 != flag2) {
        puts("-1");
    } else {
        printf("%d\n", Dinic());
    }
    return 0;
}
inline int read() {
    char ch = getchar();
    int x = 0;
    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
inline void add(int x, int y, int l, int s) {
    cost[cnt] = s;
    flews[cnt] = l;
    to[cnt] = y;
    next[cnt] = head[x];
    head[x] = cnt++;
    cost[cnt] = -s;
    flews[cnt] = 0;
    to[cnt] = x;
    next[cnt] = head[y];
    head[y] = cnt++;
}
inline int SPFA() {
    memset(min, INF, sizeof(min));
    memset(dis, INF, sizeof(dis));
    std::queue<int> q;
    q.push(S);
    dis[S] = 0;
    vis[S] = 1;
    while (!q.empty()) {
        int top = q.front();
        q.pop();
        vis[top] = 0;
        for (int i = head[top]; i != -1; i = next[i]) {
            if (dis[to[i]] > dis[top] + cost[i] && flews[i]) {
                if (!vis[to[i]]) {
                    vis[to[i]] = 1;
                    q.push(to[i]);
                }
                from[to[i]] = i;
                dis[to[i]] = dis[top] + cost[i];
                min[to[i]] = std::min(min[top], flews[i]);
            }
        }
    }
    return dis[T] != INF;
}
inline int find() {
    for (int i = T; i != S; i = to[from[i] ^ 1]) {
        flews[from[i]] -= min[T], flews[from[i] ^ 1] += min[T];
    }
    return min[T] * dis[T];
}
inline int Dinic() {
    int res = 0, flow = 0;
    while (SPFA()) {
        res += find();
        flow += min[T];
    }
    if (flow != flag2) {
        return -1;
    }
    return -res - sum;
}