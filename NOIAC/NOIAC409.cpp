#include <bits/stdc++.h>
const int C = 25;
int ln, lm, lk;
int ne[C], me[C], ke[C];
long long n, m, k, tmp;
int main() {
    scanf("%lld %lld %lld", &n, &m, &k);
    for (ln = 0, tmp = n; tmp; ++i) {
        ne[ln] = tmp % 2;
        tmp /= 2;
    }
    for (long long i = 0, tmp = m; tmp; ++i) {
        me[i] = tmp % 2;
        tmp /= 2;
    }
    for (long long i = 0, tmp = k; tmp; ++i) {
        ke[i] = tmp % 2;
        tmp /= 2;
    }
    return 0;
}