#include <bits/stdc++.h>
const int N = 1000005;
int n;
int a[N];
int main() {
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    scanf("%d", &n);
    a[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i]) {
            continue;
        }
        for (int j = (i << 1); j <= n; j += i) {
            a[j] = 1;
        }
    }
    if (n & 1) {
        if (a[n - 2]) {
            printf("NO WAY!\n");
        } else {
            printf("%d=2+%d\n", n, n - 2);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            if (!a[i] & !a[n - i]) {
                printf("%d=%d+%d\n", n, i, n - i);
                break;
            }
        }
    }
    return 0;
}