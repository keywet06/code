#include <bits/stdc++.h>
long long x, y;
long long gcd(long long, long long);
int main() {
    scanf("%lld %lld", &x, &y);
    printf("%lld\n", gcd(x, y));
    return 0;
}
inline long long gcd(long long x, long long y) {
    return x % y ? gcd(y, x % y) : y;
}