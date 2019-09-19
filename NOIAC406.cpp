#include <bits/stdc++.h>
class fim;
const int N = 100005;
const long long mod = 10000007;
class fim {
    public:
        long long a11, a12, a21, a22;
        fim();
        fim(long long, long long, long long, long long);
};
fim fim1(1, 0, 0, 1), fibm(0, 1, 1, 1);
int n, k;
long long sum;
long long a[N];
fim operator * (fim, fim);
fim operator ^ (fim, long long);
long long fi(int);
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n - 2; ++i) {
        sum += a[i];
    }
    if (a[n] < 0) {
        printf("%lld\n", (sum + (a[n - 1] + a[n]) * (k + 1)) % mod);
        return 0;
    }
    if (a[n - 1] < 0) {
        while (k && a[n - 1] < 0) {
            (sum += a[n - 1] + mod) %= mod;
            a[n - 1] += a[n];
            --k;
        }
        std::sort(a + n - 1, a + n + 1);
    }
    sum = (fi(k + 2) * a[n - 1] + fi(k + 3) * a[n] - a[n] + sum + mod) % mod;
    while (sum < 0) {
        (sum += mod * mod) %= mod;
    }
    printf("%lld\n", sum);
    return 0;
}
inline fim::fim() {
    this->a11 = this->a12 = this->a21 = this->a22 = 0;
}
inline fim::fim(long long b11, long long b12, long long b21, long long b22) {
    this->a11 = b11;
    this->a12 = b12;
    this->a21 = b21;
    this->a22 = b22;
}
inline fim operator * (fim a, fim b) {
    fim c;
    (c.a11 = a.a11 * b.a11 + a.a21 * b.a12) %= mod;
    (c.a12 = a.a21 * b.a11 + a.a22 * b.a12) %= mod;
    (c.a21 = a.a11 * b.a21 + a.a21 * b.a22) %= mod;
    (c.a22 = a.a21 * b.a21 + a.a22 * b.a22) %= mod;
    return c;
}
inline fim operator ^ (fim a, long long b) {
    return b ? ((a * a) ^ (b / 2)) * (b & 1 ? a : fim1) : fim1;
}
inline long long fi(int n) {
    fim tmp = fibm ^ (n - 1);
    return (tmp.a11 + tmp.a12) % mod;
}
