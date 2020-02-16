#include <bits/stdc++.h>
const int N = 1000;
const int Np = N + 5;
struct point {
    int x, y;
};
bool vis[Np][Np];
int W, h, n, Q, a, b, t, x, y, dx, dy, l, r;
point p[Np];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> W >> h >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i].x >> p[i].y;
    }
    p[n + 1] = p[1];
    for (int i = 1; i <= n; ++i) {
        if (p[i].x == p[i + 1].x) {
            l = std::min(p[i].y, p[i + 1].y);
            r = std::max(p[i].y, p[i + 1].y);
            for (int j = l; j <= r; ++j) {
                vis[p[i].x][j] = 1;
            }
        } else {
            l = std::min(p[i].x, p[i + 1].x);
            r = std::max(p[i].x, p[i + 1].x);
            for (int j = l; j <= r; ++j) {
                vis[j][p[i].y] = 1;
            }
        }
    }
    std::cin >> Q;
    while (Q--) {
        std::cin >> a >> b;
        t = 0;
        x = a;
        y = b;
        dx = dy = 1;
        while (1) {
            if (vis[x][y]) {
                std::cout << t << ' ' << x << ' ' << y << '\n';
                break;
            }
            if (t && x == a && y == b && dx == 1 && dy == 1) {
                std::cout << -1 << '\n';
                break;
            }
            ++t, x += dx, y += dy;
            if (x == 0 || x == W) {
                dx = -dx;
            }
            if (y == 0 || y == h) {
                dy = -dy;
            }
        }
    }
    return 0;
}