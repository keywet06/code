#include <bits/stdc++.h>

#define for2(x) for (int x = 0; x < 2; ++x)

using int64 = long long;

const int P = int(1e9) + 7;

inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T, k;
    std::cin >> T >> k;
    while (T--) {
        int64 n, m;
        std::cin >> n >> m;
        std::stack<int> sn, sm;
        while (n || m) sn.push(n % k), sm.push(m % k), n /= k, m /= k;
        std::vector<int> vn, vm;
        while (!sn.empty()) {
            vn.push_back(sn.top()), vm.push_back(sm.top());
            sn.pop(), sm.pop();
        }
        n = vn.size();
        int f[n + 1][2][2][2][2];
        memset(f, 0, sizeof(f));
        f[0][1][1][1][1] = 1;
        for (int i = 0, I = 1; i < n; ++i, ++I) {
            for2(a) for2(b) for2(c) for2(d) {
                int X = k - 1, u = f[i][a][b][c][d];
                if (a) X = vn[i];
                for (int x = 0; x <= X; ++x) {
                    int Y = k - 1;
                    if (b) Y = vm[i];
                    if (c) Y = std::min(Y, x);
                    for (int y = 0; y <= Y; ++y) {
                        Adds(f[I][a && x == vn[i]][b && y == vm[i]][c && x == y]
                              [d && x >= y],
                             u);
                    }
                }
            }
        }
        int Ans = 0;
        for2(a) for2(b) for2(c) Adds(Ans, f[n][a][b][c][0]);
        std::cout << Ans << std::endl;
    }
    return 0;
}