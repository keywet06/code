#include <bits/stdc++.h>
class ma {
    public:
        long long a[5 + 1][5 + 1];
        ma();
};
const long long mod = 1e9 + 7;
ma z, a, b;
int n, v, x, ans;
ma operator * (ma, ma);
ma ju(int);
int main() {
    for (int i = 1; i < 5; ++i) {
        z.a[i + 1][i] = 1;
    }
    scanf("%d %d", &n, &v);
    a.a[1][0] = 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        for (int j = x; j <= 5; ++j) {
            a.a[1][j] += a.a[1][j - x];
        }
        ++z.a[5 + 1 - x][5];
    }
    if (v <= 5) {
        printf("%lld\n", a.a[1][v]);
        return 0;
    }
    b = a;
    for (int i = 1; i <= v - 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            printf("%lld ", b.a[1][j]);
        }
        printf("\n");
        b = b * z;
    }
    // b = a * ju(v - 5);
    printf("%lld\n", b.a[1][5]);
    return 0;
}
inline ma::ma() {
    memset(a, 0, sizeof(a));
}
inline ma operator * (ma x, ma y) {
    ma c;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            for (int k = 1; k <= 5; ++k) {
                c.a[i][j] += x.a[i][k] * y.a[k][j];
                c.a[i][j] %= mod;
            }
        }
    }
    return c;
}
inline ma ju(int x) {
    if (x == 1) {
        return z;
    }
    ma d = ju(x / 2);
    if (x & 1) {
        return d * d * z;
    } else {
        return d * d;
    }
}