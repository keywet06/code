#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

const int N = 1005;
const int di[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int n, k, x, y, r, c, t;
int map[N][N], vis[N][N];

inline int answer(int i) {
    for (i = i + 1; i < n; ++i) std::cin >> x >> y;
    return 0;
}

inline int dfs1(int x, int y) {
    if (vis[x][y] == (c << 1)) return 0;
    int ret = (vis[x][y] = c << 1, 0), nx, ny;
    for (int i = 0; i < 4; ++i) {
        nx = x + di[i][0], ny = y + di[i][1];
        if (map[nx][ny] == 0) ++ret;
        if (map[nx][ny] == r) ret += dfs1(nx, ny);
    }
    return ret;
}

inline int dfs2(int x, int y) {
    if (vis[x][y] == (c << 1 | 1)) return 0;
    int ret = (vis[x][y] = c << 1 | 1, 0), nx, ny;
    for (int i = 0; i < 4; ++i) {
        nx = x + di[i][0], ny = y + di[i][1];
        if (map[nx][ny] == 0) ++ret;
        if (map[nx][ny] == 3 - r) ret += dfs2(nx, ny);
    }
    return ret;
}

inline void dfs3(int x, int y) {
    int nx, ny;
    map[x][y] = 0;
    for (int i = 0; i < 4; ++i) {
        nx = x + di[i][0], ny = y + di[i][1];
        if (map[nx][ny] == 3 - r) dfs3(nx, ny);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 0; (c = i + 1) <= n; ++i) {
        std::cin >> x >> y, r = (i & 1) + 1;
        if (map[x][y]) return std::cout << "illegal" << '\n', answer(i);
        map[x][y] = r;
        int nx, ny;
        for (int j = 0; j < 4; ++j) {
            nx = x + di[j][0], ny = y + di[j][1];
            if (map[nx][ny] == 3 - r && !dfs2(nx, ny)) dfs3(nx, ny);
        }
        if (!dfs1(x, y)) return std::cout << "illegal" << '\n', answer(i);
        nx = x, ny = y, t = -1;
        while (map[nx][ny] == r) --nx, --ny, ++t;
        nx = x, ny = y;
        while (map[nx][ny] == r) ++nx, ++ny, ++t;
        if (t >= k) {
            return std::cout << (i & 1 ? "Bob " : "Alice ") << c << '\n',
                   answer(i);
        }
        nx = x, ny = y, t = -1;
        while (map[nx][ny] == r) --nx, ++ny, ++t;
        nx = x, ny = y;
        while (map[nx][ny] == r) ++nx, --ny, ++t;
        if (t >= k) {
            return std::cout << (i & 1 ? "Bob " : "Alice ") << c << '\n',
                   answer(i);
        }
        nx = x, ny = y, t = -1;
        while (map[nx][ny] == r) --nx, ++t;
        nx = x, ny = y;
        while (map[nx][ny] == r) ++nx, ++t;
        if (t >= k) {
            return std::cout << (i & 1 ? "Bob " : "Alice ") << c << '\n',
                   answer(i);
        }
        nx = x, ny = y, t = -1;
        while (map[nx][ny] == r) --ny, ++t;
        nx = x, ny = y;
        while (map[nx][ny] == r) ++ny, ++t;
        if (t >= k) {
            return std::cout << (i & 1 ? "Bob " : "Alice ") << c << '\n',
                   answer(i);
        }
    }
    return std::cout << "draw" << '\n', answer(n);
}