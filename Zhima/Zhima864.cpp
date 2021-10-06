#include <bits/stdc++.h>

using pair = std::pair<int, int>;

const int N = 1005;
const int A = 4;
const int B = 2;
const int C = 16;
const int r[C] = {0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1};
const int tx[A][B] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int n, m, nx, ny, ux, uy, ans, x, y, l, r;
int vis[N][N], f[N][N];

std::string s[N];

std::queue<pair> q;

inline void check(int u) {

}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) std::cin >> s[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '#') continue;
            vis[i][j] = 1;
            for (int t = 0; t < A; ++t) {
                nx = i + tx[t][0], ny = j + tx[t][1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (s[nx][ny] == '.') continue;
                vis[nx][ny] = f[nx][ny] = 1;
                q.push(std::make_pair(nx, ny));
            }
        }
    }
    while (!q.empty()) {
        ux = q.front().first, uy = q.front().second, q.pop();
        for (int t = 0; t < A; ++t) {
            nx = ux + tx[t][0], ny = uy + tx[t][1];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny]) continue;
            f[nx][ny] = f[ux][uy] + 1, vis[nx][ny] = 1;
            q.push(std::make_pair(nx, ny));
        }
    }
    ans = n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '.') continue;
            x = y = 0;
            for (int t = 0; t < A; ++t) {
                nx = i + tx[t][0], ny = j + tx[t][1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                x |= f[nx][ny] == f[i][j] + 1;
                y |= (f[nx][ny] == f[i][j]) << t;
            }
            if (!x && !r[y]) ans = std::min(ans, f[i][j] - 1);
        }
    }
    std::cout << ans << std::endl;
    return 0;
}