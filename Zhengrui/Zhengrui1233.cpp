#include <bits/stdc++.h>
const int N = 1500;
const int Np = N + N;
const int NptNp = Np * Np;
const int cap[2][4] = {{-1, 0, 0, 1}, {0, -1, 1, 0}};
int i, j, ans, n, m, q, x, y, z, w, head, tail, nx, ny, sx, sy, k;
int lx[NptNp], ly[NptNp];
int a[Np][Np], vis[Np][Np];
std::string s;
bool pd(int a, int b, int c, int d);
inline bool pd(int xl, int yl, int xr, int yr) {
    return a[xr][yr] - a[xl - 1][yr] - a[xr][yl - 1] + a[xl - 1][yl - 1] == 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> q;
    for (i = 1; i <= n; ++i) {
        std::cin >> s;
        for (j = 1; j <= m; ++j) {
            a[i][j] = s[j - 1] == '1';
        }
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            a[i][j] += a[i - 1][j];
        }
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            a[i][j] += a[i][j - 1];
        }
    }
    if (!a[n][m]) {
        for (i = 1; i <= q; ++i) {
            std::cin >> x >> y >> z >> w;
            z -= x;
            w -= y;
            std::cout << (n - z) * (m - w) << std::endl;
        }
        return 0;
    }
    for (i = 1; i <= q; ++i) {
        std::cin >> x >> y >> z >> w;
        z -= x;
        w -= y;
        n -= z;
        m -= w;
        ans = 0;
        head = 1;
        tail = 1;
        lx[tail] = x;
        ly[tail] = y;
        vis[x][y] = i;
        while (head <= tail) {
            sx = lx[head];
            sy = ly[head];
            ++head;
            ++ans;
            for (k = 0; k < 4; ++k) {
                nx = sx + cap[0][k];
                ny = sy + cap[1][k];
                if (nx > 0 && ny > 0 && nx <= n && ny <= m && pd(nx, ny, nx + z, ny + w) && vis[nx][ny] != i) {
                    ++tail;
                    vis[nx][ny] = i;
                    lx[tail] = nx;
                    ly[tail] = ny;
                }
            }
        }
        n += z;
        m += w;
        std::cout << ans << std::endl;
    }
    return 0;
}