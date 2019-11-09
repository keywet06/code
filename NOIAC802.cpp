#include <bits/stdc++.h>
long long T, n, f;
int main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        for (long long i = 2;; ++i) {
            if (i > n) {
                break;
            }
            if (n % i == 0) {
                n = -1;
                break;
            }
            n -= n / i;
        }
        printf("%lld\n", n);
    }
    return 0;
}