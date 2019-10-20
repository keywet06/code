#include <bits/stdc++.h>
long long n, m;
__int128 power(__int128, long long);
int main() {
    scanf("%lld %lld", &n, &m);
    printf("%lld\n", (long long)(((n - 2) * power(2, n - 1) + 1) % m));
    return 0;
}
inline __int128 power(__int128 x, long long y) {
    return y ? power(x * x % m, y / 2) * (y & 1 ? x : 1) % m : 1;
}