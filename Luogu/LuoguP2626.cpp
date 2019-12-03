/*
    By keywet06
    Code-key:test
*/
#include <cmath>
#include <cstdio>
const long long mod = 1 << 31;
long long a, b, c, n;
int main() {
    scanf("%lld", &n);
    a = 1;
    b = 1;
    for (int i = 1; i <= n - 2; ++i) {
        c = (a + b) % mod;
        a = b;
        b = c;
    }
    printf("%lld=", c);
    long long i = 2;
    while (i <= sqrt(c)) {
        if (c % i == 0) {
            printf("%lld*", i);
            c /= i;
            --i;
        }
        ++i;
    }
    printf("%lld\n", c);
    return 0;
}
