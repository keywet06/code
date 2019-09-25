#include <bits/stdc++.h>
const int N = 10000005;
const int Q = 100005;
int T, R, cnt, max;
int is_p[N], prime[N];
int m[Q], n[Q];
long long divs[N], mi[N];
void Exgcd(long long, long long, long long&, long long&);
long long inv(long long);
int main() {
    scanf("%d %d", &T, &R);
    for (int i = 1; i <= T; ++i) {
        scanf("%d %d", &n[i], &m[i]);
        max = std::max(max, std::max(n[i], m[i]));
    }
    is_p[1] = 1;
    for (int i = 2; i <= max; ++i) {
        if (!is_p[i]) {
            prime[++cnt] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= max; ++j) {
            is_p[i * prime[j]] = prime[j];
            if (!(i % prime[j])) {
                break;
            }
        }
    }
    divs[0] = mi[0] = 1;
    for (int i = 1; i <= max; ++i) {
        mi[i] = mi[i - 1] * i % R;
        divs[i] = divs[i - 1] * (is_p[i] ? 1 : inv(i) * (i - 1) % R) % R;
    }
    for (int i = 1; i <= T; ++i) {
        printf("%lld\n", mi[n[i]] * divs[m[i]] % R);
    }
    return 0;
}
void Exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        Exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
long long inv(long long a) {
    long long x, y;
    Exgcd(a, R, x, y);
    x = (x % R + R) % R;
    return x;
}
