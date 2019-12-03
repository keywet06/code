#include <bits/stdc++.h>
const int C = 10;
const int N = 2000005;
int n, l, now, ro;
int flag[C];
int to[N], vis[N], next[N];
long long a, m, a1, m1, a2, m2, g, c, k1, k2, tmp, t2;
std::string s, t, p, q;
void die();
int gcd(int, int);
void Exgcd(long long, long long, long long &, long long &);
long long inv(long long, long long);
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    std::cin >> s;
    std::cin >> t;
    for (int i = 0; i < n; ++i) {
        to[i] = i < n / 2 ? i * 2 : (i - n / 2) << 1 | 1;
    }
    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            continue;
        }
        now = to[i];
        p = s[i];
        q = t[i];
        while (now != i) {
            vis[now] = 1;
            p += s[now];
            q += t[now];
            now = to[now];
        }
        l = p.length();
        p = p + p;
        flag[0] = 0;
        for (int i = 0; i < l; ++i) {
            flag[1] = 1;
            for (int j = 0; j < l; ++j) {
                if (p[i + j] != q[j]) {
                    flag[1] = 0;
                    break;
                }
            }
            if (flag[1]) {
                flag[0] = 1;
                ro = i;
                break;
            }
        }
        if (!flag[0]) {
            die();
        }
        if (!flag[2]) {
            flag[2] = 1;
            a = ro;
            m = l;
            continue;
        }
        a1 = a;
        m1 = m;
        a2 = ro;
        m2 = l;
        g = gcd(m1, m2);
        c = a2 - a1;
        Exgcd(m1, m2, k1, k2);
        m = m1 / gcd(m1, m2) * m2;
        if (c % g) {
            die();
        }
        tmp = c / g * k1;
        t2 = m2 / g;
        tmp = (tmp % t2 + t2) % t2;
        (a = a1 + m1 * tmp) %= m;
    }
    printf("%lld\n", a);
    return 0;
}
inline void die() {
    printf("-1\n");
    exit(0);
}
inline int gcd(int x, int y) {
    return x % y ? gcd(y, x % y) : y;
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
long long inv(long long a, long long mod) {
    static long long x, y;
    Exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
