#include <bits/stdc++.h>
const int N = 200;
const int tw[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char ch;
int n, m, x, ans, tp;
int a[N][N];
inline void dfs(int x, int y, int t, int val) {
    tp = a[x + tw[t][0]][y + tw[t][1]];
    ans = std::max(ans, val);
    if (tp == 2) {
        return;
    }
    a[x][y] = 2;
    if (tp == 1) {
        t = (t + 1) % 4;
        if (a[x + tw[t][0]][y + tw[t][1]] == 0) {
            dfs(x + tw[t][0], y + tw[t][1], t, val + 1);
        }   
        t = (t + 2) % 4; 
        if (a[x + tw[t][0]][y + tw[t][1]] == 0) {
            dfs(x + tw[t][0], y + tw[t][1], t, val + 1);
        }
    } else {
        dfs(x + tw[t][0], y + tw[t][1], t, val + 1);
    }
    a[x][y] = 0;
}
int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        a[0][i] = 1;
        a[n + 1][i] = 1;
        a[i][0] = 1;
        a[i][n + 1] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        do {
            std::cin >> ch;
        } while (ch == ' ' || ch == '\r' || ch == '\n');
        std::cin >> x;
        a[ch - 'A' + 1][x] = 1;
    }
    dfs(1, 1, 1, 1);
    dfs(1, 1, 2, 1);
    std::cout << ans << std::endl;
    return 0;
}