#include <bits/stdc++.h>
const int N = 1005;
double x;
int n;
int a[7], b[7], d[7];
int c[N];
int main() {
    freopen("rento.in", "r", stdin);
    freopen("rento.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= 6; ++j) {
            scanf("%lf", &x);
            if (abs(x - 1.00) < 0.0001) {
                a[i] = j;
            }
        }
        b[i] = 1;
    }
    for (int i = 1; i <= 500; ++i) {
        for (int j = 1; j <= 6; ++j) {
            b[j] += a[j];
            b[j] %= n;
            if (!c[b[j]]) {
                c[b[j]] = 1;
                ++d[j];
            }
        }
    }
    for (int i = 1; i <= 6; ++i) {
        printf("%d.00\n", d[i]);
    }
    return 0;
}