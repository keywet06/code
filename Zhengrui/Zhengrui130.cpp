#include <bits/stdc++.h>

using int64 = long long;

const int64 P = 998244353;
const int64 N = 109;

int64 w[N][N];

inline int64 ksm(int64 x, int64 y) {
    int64 rtn = 1;
    while (y) {
        if (y & 1) rtn = rtn * x % P;
        x = x * x % P, y >>= 1;
    }
    return rtn;
}

inline int64 gauss(int64 n) {
    int64 res = 1;
    for (int64 i = 1; i <= n - 1; i++) {
        for (int64 j = i + 1; j <= n - 1; j++) {
            while (w[j][i]) {
                int64 t = w[i][i] / w[j][i];
                for (int64 k = i; k <= n - 1; k++) {
                    w[i][k] = (w[i][k] - t * w[j][k] + P) % P;
                }
                std::swap(w[i], w[j]);
                res = -res;
            }
        }
        res = (res * w[i][i]) % P;
    }
    return (res + P) % P;
}

int main() {
    int64 n, m;
    std::cin >> n >> m;
    std::cout << n + m - 1 << "\n";
    if (m != 2) {
        for (int64 i = 1; i <= n; i++) {
            for (int64 j = 1; j <= m; j++) {
                char c;
                std::cin >> c;
                if (c == '.') {
                    int64 x = i, y = j + n;
                    w[x][x]++, w[y][y]++, w[x][y]--, w[y][x]--;
                }
            }
        }
        std::cout << gauss(n + m) << std::endl;
    } else {
        int64 cnt = 0;
        for (int64 i = 1; i <= n; i++) {
            char x, y;
            std::cin >> x >> y;
            if (x == y) ++cnt;
        }
        std::cout << cnt * ksm(2, cnt - 1) % P << std::endl;
    }
    return 0;
}