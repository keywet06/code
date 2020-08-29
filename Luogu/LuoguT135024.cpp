#include <bits/stdc++.h>
const int N = 25;
int n, m, q, u, v, c, stim, spoint;
int st[N], en[N], atim[N], btim[N], itim[N], ipoint[N];
int f[N][N], dp[N][N];
std::set<int> point, tim;
std::map<int, int> points, tims;
int main() {
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            f[i][j] = 100000000 * (i != j);
        }
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> v >> c;
        f[u][v] = f[v][u] = std::min(f[u][v], c);
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> st[i] >> en[i] >> atim[i] >> btim[i];
        point.insert(st[i]);
        point.insert(en[i]);
        tim.insert(atim[i]);
        tim.insert(btim[i]);
    }
    tim.insert(0);
    for (std::set<int>::iterator it = tim.begin(); it != tim.end(); ++it) {
        itim[++stim] = *it;
        tims[*it] = stim;
    }
    for (std::set<int>::iterator it = point.begin(); it != point.end(); ++it) {
        ipoint[++spoint] = *it;
        points[*it] = spoint;
    }
    dp[1][1] = 0;
    for (int i = 1; i <= stim; ++i) {
        for (int j = 1; j < i; ++j) {
            for (int k = 1; k <= spoint; ++k) {
                for (int l = 1; l <= spoint; ++l) {
                    if (itim[i] - itim[j] >= f[ipoint[k]][ipoint[l]]) {
                        dp[i][k] = std::max(dp[i][k], dp[j][l]);
                    }
                }
            }
        }
        for (int j = 1; j <= q; ++j) {
            if (itim[btim[j]] == i) {
                dp[i][points[en[j]]] =
                    std::max(dp[i][ipoint[en[j]]],
                             dp[itim[atim[j]]][ipoint[st[j]]] + 1);
            }
        }
    }
    c = 0;
    for (int i = 1; i <= spoint; ++i) {
        c = std::max(c, dp[stim][i]);
    }
    std::cout << c << std::endl;
    return 0;
}