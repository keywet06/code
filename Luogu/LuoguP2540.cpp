#include <bits/stdc++.h>
const int N = 30;
int T, n, y, x, ans;
int now[N];
inline void init() {
    memset(now, 0, sizeof(now));
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x, &y);
        if ((x >= 3) && (x <= 13)) {
            now[x - 2]++;
        }
        if (x == 0) {
            now[14]++;
        }
        if (x == 1) {
            now[12]++;
        }
        if (x == 2) {
            now[13]++;
        }
    }
    ans = n;
}
inline int checktask() {
    int res[5], temp[14], ret = 0;
    memset(res, 0, sizeof(res));
    for (int i = 1; i <= 14; i++) {
        res[now[i]]++;
    }
    for (int i = 1; i <= 14; i++) {
        temp[i] = now[i];
    }
    if (res[4] && (res[2] > 2 || res[3] > 2)) {
        for (int i = 1; i <= 14; i++) {
            if (temp[i] == 4) {
                for (int j = 1; j <= 14; j++) {
                    if ((j == i) || (temp[j] != 2)) {
                        continue;
                    }
                    if (temp[i] < 4) {
                        break;
                    }
                    for (int k = 1; k <= 14; k++) {
                        if ((k == j) || (k == i)) {
                            continue;
                        }
                        if (temp[k] == 2) {
                            temp[i] -= 4;
                            temp[j] -= 2;
                            temp[k] -= 2;
                            res[4]--;
                            ret++;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (res[4] && (res[2] || res[3] || (res[1]))) {
        for (int i = 1; i <= 14; i++) {
            if (temp[i] == 4) {
                for (int j = 1; j <= 14; j++) {
                    if ((j == i) || (temp[j] != 1)) {
                        continue;
                    }
                    if (temp[i] != 4) {
                        break;
                    }
                    for (int k = 1; k <= 14; k++) {
                        if ((k == j) || (k == i)) {
                            continue;
                        }
                        if (temp[k] == 1) {
                            temp[i] -= 4;
                            temp[j]--;
                            temp[k]--;
                            ret++;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (res[4] && (res[2] || res[3])) {
        for (int i = 1; i <= 14; i++) {
            if (temp[i] == 4) {
                for (int j = 1; j <= 14; j++) {
                    if (j == i) {
                        continue;
                    }
                    if (temp[j] == 2) {
                        temp[i] -= 4;
                        ret++;
                        temp[j] -= 2;
                        res[4]--;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= 14; i++) {
        if (temp[i] >= 3) {
            for (int j = 1; j <= 14; j++) {
                if (j == i) {
                    continue;
                }
                if (temp[j] == 2) {
                    temp[i] -= 3;
                    temp[j] -= 2;
                    ret++;
                    break;
                }
                if (temp[j] == 1) {
                    temp[i] -= 3;
                    temp[j]--;
                    ret++;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= 14; i++) {
        if (temp[i] == 4) {
            temp[i] -= 4, ret++;
        } else if (temp[i] == 3) {
            temp[i] -= 3, ret++;
        } else if (temp[i] == 2) {
            temp[i] -= 2, ret++;
        } else if (temp[i]) {
            temp[i]--, ret++;
        }
    }
    return ret;
}
inline void dfs(int deep) {
    if (deep >= ans) {
        return;
    }
    for (int i = 1; i <= 14; i++) {
        if (now[i]) {
            break;
        }
        if (i == 14) {
            ans = deep;
            return;
        }
    }
    printf("deep1 %d.\n", deep);
    int temp = checktask();
    printf("deep2 %d.\n", deep);
    if (temp + deep < ans) {
        ans = temp + deep;
    }
    int res[5];
    memset(res, 0, sizeof(res));
    for (int i = 1; i <= 14; i++) {
        res[now[i]]++;
    }
    if (res[3] >= 3) {
        for (int i = 1; i <= 10; i++) {
            for (int l = 2; l <= 12; l++) {
                for (int p = i; p <= l + i; p++) {
                    if ((now[p] < 3) || (p > 12)) {
                        break;
                    } else {
                        if (p == l + i) {
                            for (int q = p - l; q <= p; q++) {
                                now[q] -= 3;
                            }
                            res[3] -= l + 1;
                            dfs(deep + 1);
                            res[3] += l + 1;
                            for (int q = p - l; q <= p; q++) {
                                now[q] += 3;
                            }
                        }
                    }
                }
            }
        }
    }
    if (res[2] >= 3) {
        for (int i = 1; i <= 10; i++) {
            for (int l = 2; l <= 12; l++) {
                for (int p = i; p <= l + i; p++) {
                    if ((now[p] < 2) || (p > 12)) {
                        break;
                    } else {
                        if (p == l + i) {
                            for (int q = p - l; q <= p; q++) {
                                now[q] -= 2;
                            }
                            res[2] -= l + 1;
                            dfs(deep + 1);
                            res[2] += l + 1;
                            for (int q = p - l; q <= p; q++) {
                                now[q] += 2;
                            }
                        }
                    }
                }
            }
        }
    }
    if (res[1] + res[2] + res[3] > 5) {
        for (int i = 1; i <= 10; i++) {
            for (int l = 4; l <= 12; l++) {
                for (int p = i; p <= i + l; p++) {
                    if ((!now[p]) || (p > 12)) {
                        break;
                    } else {
                        if (p == l + i) {
                            for (int q = p - l; q <= p; q++) {
                                now[q]--;
                            }
                            dfs(deep + 1);
                            for (int q = p - l; q <= p; q++) {
                                now[q]++;
                            }
                        }
                    }
                }
            }
        }
    }
}
int main() {
    scanf("%d %d", &T, &n);
    while (T--) {
        init();
        dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}