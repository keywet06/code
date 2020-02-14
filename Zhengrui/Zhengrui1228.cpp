#include <bits/stdc++.h>
const int C = 3;
const int N = 4005;
struct node {
    int l, r, v;
};
int n, m, len, w, u, x, y, p;
node aw[N];
std::vector<int> vector[N];
long long st[N];
long long dp[N][N][C];
std::istream &operator>>(std::istream &in, node &x);
inline std::istream &operator>>(std::istream &in, node &x) {
    return in >> x.v >> x.l >> x.r;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> x >> y;
    for (int i = 1; i <= m; i++) {
        std::cin >> aw[i];
        aw[i].v--;
        st[++p] = aw[i].l;
        st[++p] = aw[i].l - 1;
        st[++p] = aw[i].r;
        st[++p] = aw[i].r + 1;
    }
    std::sort(st + 1, st + p + 1);
    p = std::unique(st + 1, st + p + 1) - st - 1;
    for (int i = 1; i <= m; i++) {
        aw[i].l = std::lower_bound(st + 1, st + p + 1, aw[i].l) - st;
        aw[i].r = std::lower_bound(st + 1, st + p + 1, aw[i].r) - st;
        vector[aw[i].l].push_back(i);
    }
    for (int i = 1; i <= p; i++) {
        for (int j = i - 1; j <= p; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i + 1][std::max(i, j)][k] =
                    std::max(dp[i + 1][std::max(i, j)][k], dp[i][j][k]);
                len = vector[i].size();
                for (int l = 0; l < len; l++) {
                    u = vector[i][l];
                    w = aw[u].r;
                    if (w > j) {
                        dp[i + 1][w][aw[u].v] = std::max(
                            dp[i + 1][w][aw[u].v],
                            dp[i][j][k] + (st[w] - st[j]) * x -
                                (aw[u].v != k) * (st[j] - st[i] + 1) * (x + y));
                    }
                }
            }
        }
    }
    std::cout << std::max(std::max(dp[p + 1][p][0], dp[p + 1][p][1]),
                          dp[p + 1][p][2])
              << std::endl;
    return 0;
}
