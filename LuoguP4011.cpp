#include <bits/stdc++.h>
const int N = 12;
const int L = 10005;
const int lx[4] = {-1, 0, 0, 1};
const int ly[4] = {0, -1, 1, 0};
struct node {
    int x, y, l;
};
node t, v;
int n, m, p, x, y, z, w, s;
int b[N][N];
int dis[N][N][L], vis[N][N][L];
int a[N][N][N][N];
int main() {
    scanf("%d %d %d", &n, &m, &p);
    scanf("%d", &p);
    while (p--) {
        scanf("%d %d %d %d %d", &x, &y, &z, &w, &s);
        if (s == 0) {
            s = 1 << 11;
        } else {
            s = 1 << (s - 1);
        }
        a[x][y][z][w] |= s;
        a[z][w][x][y] |= s;
    }
    scanf("%d", &p);
    while (p--) {
        scanf("%d %d %d", &x, &y, &z);
        b[x][y] |= 1 << (z - 1);
    }
    std::queue<node> queue;
    t.x = 1;
    t.y = 1;
    t.l = 0;
    vis[1][1][0] = 1;
    queue.push(t);
    while (!queue.empty()) {
        v = queue.front();
        queue.pop();
        for (int i = 0; i < 4; ++i) {
            t.x = v.x + lx[i];
            t.y = v.y + ly[i];
            if (t.x < 1 || t.x > n || t.y < 1 || t.y > m) {
                continue;
            }
            t.l = a[v.x][v.y][t.x][t.y];
            if ((t.l & v.l) != t.l) {
                continue;
            }
            t.l = v.l | b[t.x][t.y];
            if (vis[t.x][t.y][t.l]) {
                continue;
            }
            vis[t.x][t.y][t.l] = 1;
            dis[t.x][t.y][t.l] = dis[v.x][v.y][v.l] + 1;
            if (t.x == n && t.y == m) {
                printf("%d\n", dis[t.x][t.y][t.l]);
                return 0;
            }
            queue.push(t);
        }
    }
    printf("-1\n");
    return 0;
}