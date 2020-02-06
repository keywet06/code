#include <bits/stdc++.h>
const int K = 11;
const int N = 3005;
int n;
int qa[K], qb[K], qc[K], c[K];
int a[N], b[N];
long long ea[N][N], eb[N][N], ec[N][N], ed[N][N], ef[N][N], eg[N][N];
inline long long wd(int l, int r, int c) { return ea[r][c] - ea[l - 1][c]; }
inline long long C(int x, int y) { return y ? wd(qb[x], qc[x], c[y]) : 0; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= 5; ++i) {
        std::cin >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            ea[i][j] = ea[i - 1][j];
        }
        ea[i][a[i]]++;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] == a[j]) {
                eb[i][j] = 1;
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; i + j - 1 <= n; ++j) {
            eb[j][j + i - 1] +=
                eb[j][j + i - 2] + eb[j + 1][j + i - 1] - eb[j + 1][j + i - 2];
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] == a[j]) {
                ec[i][j] = 1;
            }
        }
    }
    for (int i = n - 1; i; i--) {
        for (int j = 1; i + j - 1 <= n; ++j) {
            ec[j][j + i - 1] +=
                ec[j - 1][j + i - 1] + ec[j][j + i] - ec[j - 1][j + i];
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 2; j <= n; ++j) {
            if (a[i] == a[j]) {
                ed[i][j] = wd(i + 1, j - 1, a[i]);
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; i + j - 1 <= n; ++j) {
            ed[j][j + i - 1] +=
                ed[j][j + i - 2] + ed[j + 1][j + i - 1] - ed[j + 1][j + i - 2];
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] == a[j]) {
                ef[i][j] = wd(1, i - 1, a[i]);
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] == a[j]) {
                eg[i][j] = wd(j + 1, n, a[i]);
            }
        }
    }
    for (int i = n - 1; i; i--) {
        for (int j = 1; i + j - 1 <= n; ++j) {
            ef[j][j + i - 1] +=
                ef[j - 1][j + i - 1] + ef[j][j + i] - ef[j - 1][j + i];
        }
    }
    for (int i = n - 1; i; i--) {
        for (int j = 1; i + j - 1 <= n; ++j) {
            eg[j][j + i - 1] +=
                eg[j - 1][j + i - 1] + eg[j][j + i] - eg[j - 1][j + i];
        }
    }
    for (int i = 1; i <= 5; ++i) {
        qa[i] = b[i] == b[2] ? 2 : (b[i] == b[4] ? 4 : 0);
    }
    long long ans = 0;
    for (int x = 2; x < n; x++) {
        for (int y = x + 2; y < n; y++) {
            c[2] = a[x];
            c[4] = a[y];
            if ((c[2] == c[4]) != (b[2] == b[4])) {
                continue;
            }
            if (qa[4] == 2) {
                c[4] = 0;
            }
            int cc = 0;
            long long cnt = 1;
            qb[1] = 1;
            qc[1] = x - 1;
            qb[3] = x + 1;
            qc[3] = y - 1;
            qb[5] = y + 1;
            qc[5] = n;
            for (int i = 1; i <= 5; i += 2) {
                if (qa[i]) {
                    cnt = cnt * wd(qb[i], qc[i], c[qa[i]]);
                    cc++;
                }
            }
            if (!cnt || cc == 3) {
                ans += cnt;
                continue;
            }
            if (cc == 2) {
                for (int i = 1; i <= 5; i += 2) {
                    if (!qa[i]) {
                        cnt = cnt * (qc[i] - qb[i] + 1 -
                          wd(qb[i], qc[i], c[2]) - wd(qb[i], qc[i], c[4]));
                    }
                }
                ans += cnt;
            } else if (cc == 1 && qa[1]) {
                long long r = eb[qb[3]][qc[5]] - eb[qb[3]][y] - eb[y][qc[5]];
                r -= C(3, 4) * C(5, 4);
                r -= C(3, 2) * C(5, 2);
                if (b[3] != b[5]) {
                    r = (qc[3] - qb[3] + 1 - C(3, 2) - C(3, 4)) *
                      (qc[5] - qb[5] + 1 - C(5, 2) - C(5, 4)) - r;
                }
                ans += cnt * r;
            } else if (cc == 1 && qa[3]) {
                long long r = ec[qc[1]][qb[5]];
                r -= C(1, 4) * C(5, 4);
                r -= C(1, 2) * C(5, 2);
                if (b[1] != b[5]) {
                    r = (qc[1] - qb[1] + 1 - C(1, 2) - C(1, 4)) *
                      (qc[5] - qb[5] + 1 - C(5, 2) - C(5, 4)) - r;
                }
                ans += cnt * r;
            } else if (cc == 1 && qa[5]) {
                long long r = eb[qb[1]][qc[3]] - eb[qb[1]][x] - eb[x][qc[3]];
                r -= C(1, 4) * C(3, 4);
                r -= C(1, 2) * C(3, 2);
                if (b[1] != b[3]) {
                    r = (qc[1] - qb[1] + 1 - C(1, 2) - C(1, 4)) *
                      (qc[3] - qb[3] + 1 - C(3, 2) - C(3, 4)) - r;
                }
                ans += cnt * r;
            } else if (cc == 0) {
                long long l1 = (qc[1] - qb[1] + 1 - C(1, 2) - C(1, 4)),
                          l2 = (qc[3] - qb[3] + 1 - C(3, 2) - C(3, 4)),
                          l3 = (qc[5] - qb[5] + 1 - C(5, 2) - C(5, 4)), r;
                long long t2 = ed[1][n] - ed[1][y] - ed[x][n] + ed[x][y] -
                               ef[x][y + 1] - eg[x - 1][y] -
                               C(1, 2) * C(3, 2) * C(5, 2) -
                               C(1, 4) * C(3, 4) * C(5, 4);
                if (b[1] == b[3] && b[1] == b[5]) {
                    ans += t2;
                } else if (b[1] == b[3]) {
                    r = eb[qb[1]][qc[3]] - eb[qb[1]][x] - eb[x][qc[3]];
                    r -= C(1, 2) * C(3, 2);
                    r -= C(1, 4) * C(3, 4);
                    r *= l3;
                    ans += r - t2;
                } else if (b[3] == b[5]) {
                    r = eb[qb[3]][qc[5]] - eb[qb[3]][y] - eb[y][qc[5]];
                    r -= C(3, 2) * C(5, 2);
                    r -= C(3, 4) * C(5, 4);
                    r *= l1;
                    ans += r - t2;
                } else if (b[1] == b[5]) {
                    long long r = ec[qc[1]][qb[5]];
                    r -= C(1, 2) * C(5, 2);
                    r -= C(1, 4) * C(5, 4);
                    r *= l2;
                    ans += r - t2;
                } else {
                    long long tmp = ec[qc[1]][qb[5]];
                    r = eb[qb[1]][qc[3]] - eb[qb[1]][x] - eb[x][qc[3]];
                    r -= C(1, 2) * C(3, 2);
                    r -= C(1, 4) * C(3, 4);
                    r = l1 * l2 - r;
                    r *= l3;
                    tmp -= C(1, 2) * C(5, 2);
                    tmp -= C(1, 4) * C(5, 4);
                    tmp *= l2;
                    r -= tmp - t2;
                    tmp = eb[qb[3]][qc[5]] - eb[qb[3]][y] - eb[y][qc[5]];
                    tmp -= C(3, 2) * C(5, 2);
                    tmp -= C(3, 4) * C(5, 4);
                    tmp *= l1;
                    r -= tmp - t2;
                    ans += r;
                }
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}