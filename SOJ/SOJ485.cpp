#include <bits/stdc++.h>
const int N = 30000000;
long long p, q, j, k, a, b, c, tmp, d;
long long to(long long);
long long gcd(long long, long long);
int main() {
    scanf("%lld %lld %lld", &a, &b, &c);
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("-INF\n");
                return 0;
            } else {
                printf("\"DAKNB!\"\n");
                return 0;
            }
        } else {
            if (c == 0) {
                b = 1;
            } else {
                tmp = gcd(to(b), to(c));
                b /= tmp;
                c /= tmp;
            }
            if (b < 0) {
                b = -b;
                c = -c;
            }
            printf("%lld %lld %lld %lld\n", -c, 0, 0, b);
            return 0;
        }
    } else {
        tmp = gcd(to(a), gcd(to(b), to(c)));
        a /= tmp;
        b /= tmp;
        c /= tmp;
        p = -b;
        k = 2 * a;
        q = b * b - 4 * a * c;
        j = d = 1;
        if (a < 0) {
            j = -1;
        }
        if (q < 0) {
            printf("\"DAKNB!\"\n");
            return 0;
        }
        if (q == 0) {
            j = 0;
        } else {
            for (long long i = 2; i * i * i <= q; ++i) {
                if (q % (i * i) == 0) {
                    q /= i * i;
                    j *= i;
                    --i;
                } else if (q % i == 0) {
                    q /= i;
                    d *= i;
                }
            }
            tmp = (int)(sqrt(q) + 0.1);
            if (tmp * tmp == q) {
                q = 1;
                j *= tmp;
            }
            q *= d;
        }
        if (q == 1 || q == 0) {
            p += j;
            q = j = 0;
            if (p != 0) {
                tmp = gcd(to(p), to(k));
                p /= tmp;
                k /= tmp;
            } else {
                k = 1;
            }
        } else {
            if (p == 0) {
                tmp = gcd(to(k), to(j));
            } else if (k == 0) {
                tmp = gcd(to(p), to(j));
            } else if (j == 0) {
                tmp = gcd(to(p), to(k));
            } else {
                tmp = gcd(to(p), gcd(to(k), to(j)));
            }
            p /= tmp;
            k /= tmp;
            j /= tmp;
        }
        if (k < 0) {
            k = -k;
            p = -p;
            j = -j;
        }
        if (q == 0 || j == 0) {
            q = j = 0;
        }
        printf("%lld %lld %lld %lld\n", p, j, q, k);
        return 0;
    }
    return 0;
}
inline long long to(long long x) {
    x = std::abs(x);
    if (x == 0) {
        return 1;
    }
    return x;
}
inline long long gcd(long long x, long long y) {
    return x % y == 0 ? y : gcd(y, x % y);
}
