#include <bits/stdc++.h>
const int maxn = 102;
int N, M;
int sx, sy;
int tx, ty;
char Matrix[maxn][maxn];
bool visit[maxn][maxn][12][32];
int cnt;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int snake;
struct sna {
    int x, y;
} Sna[10];
struct node {
    int x, y, step, status, s;
    node() {
        step = s = 0;
        status = 0;
    }
};
bool ok(int status, int id) {
    if (status + 1 == id)
        return true;
    else
        return false;
}
int bfs() {
    std::queue<node> Q;
    while (!Q.empty()) Q.pop();
    node n0, nx, ans;
    n0.x = sx;
    n0.y = sy;
    Q.push(n0);
    while (!Q.empty()) {
        nx = Q.front();
        Q.pop();
        int x = nx.x;
        int y = nx.y;
        int step = nx.step;
        int status = nx.status;
        int s = nx.s;
        if (x == tx && y == ty && ok(status, M + 1)) return step;
        visit[x][y][status][s] = true;
        bool flag = false;
        if (Matrix[x][y] == 'S') {
            int id;
            for (int i = 0; i < cnt; i++) {
                if (x == Sna[i].x && y == Sna[i].y) {
                    id = i;
                    break;
                }
            }
            int xx = (s >> id) & 1;
            if (xx == 1) {
                flag = true;
            } else {
                int v = (1 << id);
                int _s = s | v;
                ans.x = x;
                ans.y = y;
                ans.status = status;
                ans.s = _s;
                ans.step = step + 1;
                Q.push(ans);
            }
        } else
            flag = true;
        for (int i = 0; i < 4 && flag; i++) {
            int _x = x + dx[i];
            int _y = y + dy[i];
            if (_x >= 1 && _x <= N && _y >= 1 && _y <= N) {
                if (Matrix[_x][_y] >= '1' && Matrix[_x][_y] <= '9') {
                    int id = Matrix[_x][_y] - '0';
                    if (ok(status, id)) {
                        int _status = status + 1;
                        if (!visit[_x][_y][_status][s]) {
                            visit[_x][_y][_status][s] = true;
                            ans.x = _x;
                            ans.y = _y;
                            ans.step = step + 1;
                            ans.status = _status;
                            ans.s = s;
                            Q.push(ans);
                        }
                    } else {
                        if (!visit[_x][_y][status][s]) {
                            visit[_x][_y][status][s] = true;
                            ans.x = _x;
                            ans.y = _y;
                            ans.s = s;
                            ans.step = step + 1;
                            ans.status = status;
                            Q.push(ans);
                        }
                    }

                } else if (Matrix[_x][_y] != '#') {
                    if (!visit[_x][_y][status][s]) {
                        ans.x = _x;
                        ans.y = _y;
                        ans.status = status;
                        ans.step = step + 1;
                        ans.s = s;
                        visit[_x][_y][status][s] = true;
                        Q.push(ans);
                    }
                }
            }
        }
    }
    return -1;
}
int main() {
    while (~scanf("%d%d", &N, &M)) {
        if (N == 0 && M == 0) break;
        memset(visit, false, sizeof(visit));
        cnt = 0;
        for (int i = 1; i <= N; i++) {
            scanf("%s", Matrix[i] + 1);
            for (int j = 1; j <= N; j++) {
                if (Matrix[i][j] == 'K') {
                    sx = i;
                    sy = j;
                }
                if (Matrix[i][j] == 'T') {
                    tx = i;
                    ty = j;
                }
                if (Matrix[i][j] == 'S') {
                    Sna[cnt].x = i;
                    Sna[cnt++].y = j;
                }
            }
        }
        int res = bfs();
        if (res != -1)
            printf("%d\n", res);
        else
            printf("impossible\n");
    }
    return 0;
}