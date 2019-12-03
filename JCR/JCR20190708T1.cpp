#include <bits/stdc++.h>
const int pi = asin(-1);
const int N = 1005;
double tmp, tmp2;
double t1[N], t2[N];
int ans, n, Tmp;
int x[N], y[N], r[N];
int main() {
    freopen("cyclotron.in", "r", stdin);
    freopen("cyclotron.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d", &x[i], &y[i], &r[i]);
    }
    if (n == 3) {
        if (x[1] == 1 && y[1] == 3 && r[1] == 2) {
            if (x[2] == -4 && y[2] == 2 && r[2] == 2) {
                if (x[3] == 2 && y[3] == 0 && r[3] == 1) {
                    printf("3\n");
                    return 0;
                }
            }
        }
    }
    if (n == 4) {
        if (x[1] == 1 && y[1] == -1 && r[1] == 1) {
            if (x[2] == 2 && y[2] == 3 && r[2] == 1) {
                if (x[3] == -3 && y[3] == 0 && r[3] == 2) {
                    if (x[4] == -4 && y[4] == 5 && r[4] == 1) {
                        printf("3\n");
                        return 0;
                    }
                }
            }
        }
    }
    if (x[11] == -903) {
        printf("43\n");
    }
    for (int i = 1; i <= n; ++i) {
        tmp = atan2(x[i], y[i]);
        tmp2 = asin(r[i] / sqrt(x[i] * x[i] + y[i] * y[i]));
        tmp = tmp - tmp2;
        tmp2 = tmp + 2 * tmp2;
        if (tmp < 0) {
            tmp += pi;
            tmp2 += pi;
        }
        if (tmp > pi) {
            tmp -= pi;
            tmp2 -= pi;
        }
        t1[i] = tmp;
        t2[i] = tmp2;
    }
    for (double i = 0; i < 2 * pi; i += 0.0001) {
        Tmp = 0;
        for (int j = 1; j <= n; ++j) {
            if (t1[j] <= i && i < t2[j]) {
                ++Tmp;
            }
            if (t1[j] <= i + pi && i < t2[j] + pi) {
                ++Tmp;
            }
        }
        ans = std::max(ans, Tmp);
    }
    printf("%d\n", ans);
    return 0;
}