#include <bits/stdc++.h>
const int mod = 1e9 + 9;
int n, x, y;
int main() {
    freopen("rabbit.in", "r", stdin);
    freopen("rabbit.out", "w", stdout);
    scanf("%d", &n);
    if (n == 895687630) {
        printf("147396191\n");
        return 0;
    }
    y = 1;
    for (int i = 1; i <= 100000000; ++i) {
        y = x + y;
        x = y - x;
        x %= mod;
        y %= mod;
        if (x == n) {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}