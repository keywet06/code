#include <bits/stdc++.h>

const int B = 2;
const int N = 1005;
const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, -1, 1, 0};

struct node {
    int x, y, v, s;
};

int n, m, x, y;
int a[N][N][B];

node t, o;

std::string s[N];

std::deque<node> q;

void dfs(int x, int y, int v) {
    if (s[x][y] == '.' && !a[x][y][1]) {
        t.x = x, t.y = y, t.s = 1, t.v = o.v;
        q.push_front(t), a[x][y][1] = 1;
    }
    if (v == 2) return;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (s[nx][ny] == '.' || s[nx][ny] == '#') dfs(nx, ny, v + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> s[i], s[i] = '*' + s[i] + '*';
    for (int i = 0; i <= m + 1; ++i) s[0] += '*', s[n + 1] += '*';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i][j] == 'H') t.x = i, t.y = j;
        }
    }
    q.push_back(t);
    while (!q.empty()) {
        o = q.front(), q.pop_front();
        if (!o.s) dfs(o.x, o.y, 0);
        for (int i = 0; i < 4; ++i) {
            t.x = o.x + dx[i], t.y = o.y + dy[i], t.s = o.s, t.v = o.v + 1;
            if (s[t.x][t.y] == '.' && !a[t.x][t.y][o.s]) {
                q.push_back(t), a[t.x][t.y][o.s] = 1;
            }
            if (s[t.x][t.y] == 'D') {
                std::cout << t.v << std::endl;
                exit(0);
            }
        }
    }
    std::cout << -1 << std::endl;
    return 0;
}