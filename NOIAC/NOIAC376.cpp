#include <bits/stdc++.h>
unsigned long long a[10];
int T;
int main() {
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i <= 8; i++) {
            scanf("%llu", &a[i]);
        }
        a[9] = 0;
        if (a[8] == 0) {
            for (int i = 0; i <= 7; i++) {
                a[9] += (1LL << a[i]);
            }
            printf("%llu\n", a[9]);
        } else {
            a[8]--;
            for (int i = 0; i <= 7; i++) {
                a[9] += (1LL << a[i]);
            }
            a[9] += a[8];
            if (a[9] == 18446744073709551615ULL) {
                printf("18446744073709551616\n");
            } else {
                printf("%llu\n", a[9] + 1);
            }
        }
    }
    return 0;
}