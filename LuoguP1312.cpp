#include <bits/stdc++.h>
const int A = 7;
const int B = 5;
const int C = 10000;
int n, x, y;
int ax[C], ay[C], ag[C], as[C];
int bfl[B][A];
int sck[C][B][A];
void dfs(int, int);
int main() {
    scanf("%d", &n);
    for (int i = 0; i < B; ++i) {
        scanf("%d", &x);
        for (int j = 0; x; ++j) {
            sck[0][i][j] = x;
            ++y;
            scanf("%d", &x);
        }
    }
    dfs(0, y);
    printf("-1\n");
    return 0;
}
inline void dfs(int p, int y) {
    // printf("Debug: dfs(%d, %d)\n", p, y);
    if (p == n) {
        if (y) {
            return;
        }
        for (int i = 0; i <= n; ++i) {
            printf("%d %d %d %d\n", ax[i], ay[i], ag[i], as[i]);
            for (int j = A - 1; ~j; --j) {
                for (int k = 0; k < B; ++k) {
                    printf("%d ", sck[i][k][j]);
                }
                printf("\n");
            }
        }
        exit(0);
    }
    // if (y) {
    //     return;
    // }
    int flag, g, m;
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < A; ++j) {
            if (!sck[p][i][j]) {
                continue;
            }
            // printf("Debug: 1\n");
            if (i < B - 1) {
                for (int i = 0; i < B; ++i) {
                    for (int j = 0; j < A; ++j) {
                        sck[p + 1][i][j] = sck[p][i][j];
                    }
                }
                std::swap(sck[p + 1][i + 1][j], sck[p + 1][i][j]);
                g = y;
                do {
                    flag = 0;
                    for (int i = 0; i < B; ++i) {
                        m = 0;
                        for (int j = 0; j < A; ++j) {
                            if (sck[p + 1][i][j]) {
                                sck[p + 1][i][m++] = sck[p + 1][i][j];
                            }
                        }
                    }
                    memset(bfl, 0, sizeof(bfl));
                    for (int i = 0; i < B; ++i) {
                        m = sck[p + 1][i][0] > 0;
                        for (int j = 1; j < A; ++j) {
                            if (sck[p + 1][i][j] && sck[p + 1][i][j - 1] == sck[p + 1][i][j]) {
                                ++m;
                            } else {
                                if (m >= 3) {
                                    flag = 1;
                                    for (int k = j - m; k < j; ++k) {
                                        bfl[i][k] = 1;
                                    }
                                }
                                m = sck[p + 1][i][j] > 0;
                            }
                        }
                        if (m >= 3) {
                            flag = 1;
                            for (int k = A - m; k < A; ++k) {
                                bfl[i][k] = 1;
                            }
                        }
                    }
                    for (int i = 0; i < A; ++i) {
                        m = sck[p + 1][0][i] > 0;
                        for (int j = 1; j < B; ++j) {
                            if (sck[p + 1][j][i] && sck[p + 1][j - 1][i] == sck[p + 1][j][i]) {
                                ++m;
                            } else {
                                if (m >= 3) {
                                    flag = 1;
                                    for (int k = j - m; k < j; ++k) {
                                        bfl[k][i] = 1;
                                    }
                                }
                                m = sck[p + 1][j][i] > 0;
                            }
                        }
                        if (m >= 3) {
                            flag = 1;
                            for (int k = B - m; k < B; ++k) {
                                bfl[k][i] = 1;
                            }
                        }
                    }
                    for (int i = 0; i < B; ++i) {
                        for (int j = 0; j < A; ++j) {
                            if (bfl[i][j] && sck[p + 1][i][j]) {
                                sck[p + 1][i][j] = 0;
                                --g;
                                // printf("Debug: delete %d, %d\n", i, j);
                            }
                        }
                    }
                } while (flag);
                ax[p] = i;
                ay[p] = j;
                ag[p] = -1;
                as[p] = g;
                dfs(p + 1, g);
            }
            // printf("Debug: 2\n");
            if (i) {
                for (int i = 0; i < B; ++i) {
                    for (int j = 0; j < A; ++j) {
                        sck[p + 1][i][j] = sck[p][i][j];
                    }
                }
                // printf("Debug: 4\n");
                std::swap(sck[p + 1][i - 1][j], sck[p + 1][i][j]);
                g = y;
                do {
                    flag = 0;
                    for (int i = 0; i < B; ++i) {
                        m = 0;
                        for (int j = 0; j < A; ++j) {
                            if (sck[p + 1][i][j]) {
                                sck[p + 1][i][m++] = sck[p + 1][i][j];
                            }
                        }
                    }
                    memset(bfl, 0, sizeof(bfl));
                    for (int i = 0; i < B; ++i) {
                        m = sck[p + 1][i][0] > 0;
                        for (int j = 1; j < A; ++j) {
                            if (sck[p + 1][i][j] && sck[p + 1][i][j - 1] == sck[p + 1][i][j]) {
                                ++m;
                            } else {
                                if (m >= 3) {
                                    flag = 1;
                                    for (int k = j - m; k < j; ++k) {
                                        bfl[i][k] = 1;
                                    }
                                }
                                m = sck[p + 1][i][j] > 0;
                            }
                        }
                        if (m >= 3) {
                            flag = 1;
                            for (int k = A - m; k < A; ++k) {
                                bfl[i][k] = 1;
                            }
                        }
                    }
                    for (int i = 0; i < A; ++i) {
                        m = sck[p + 1][0][i] > 0;
                        for (int j = 1; j < B; ++j) {
                            if (sck[p + 1][j][i] && sck[p + 1][j - 1][i] == sck[p + 1][j][i]) {
                                ++m;
                            } else {
                                if (m >= 3) {
                                    flag = 1;
                                    for (int k = j - m; k < j; ++k) {
                                        bfl[k][i] = 1;
                                    }
                                }
                                m = sck[p + 1][j][i] > 0;
                            }
                        }
                        if (m >= 3) {
                            flag = 1;
                            for (int k = B - m; k < B; ++k) {
                                bfl[k][i] = 1;
                            }
                        }
                    }
                    for (int i = 0; i < B; ++i) {
                        for (int j = 0; j < A; ++j) {
                            if (bfl[i][j] && sck[p + 1][i][j]) {
                                sck[p + 1][i][j] = 0;
                                --g;
                                // printf("Debug: delete %d, %d\n", i, j);
                            }
                        }
                    }
                } while (flag);
                ax[p] = i;
                ay[p] = j;
                ag[p] = -1;
                as[p] = g;
                dfs(p + 1, g);
            }
            // printf("Debug: 3\n");
        }
    }
}
