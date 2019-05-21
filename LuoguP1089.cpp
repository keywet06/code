#include <bits/stdc++.h>
int cun, now, x;
int main() {
    for (int i = 1; i <= 12; ++i) {
        now += 300;
        scanf("%d", &x);
        if (x > now) {
            printf("%d\n", -i);
            return 0;
        }
        now -= x;
        cun += now / 100;
        now %= 100;
    }
    printf("%d\n", cun * 120 + now);
    return 0;
}