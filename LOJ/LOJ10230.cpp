#include <bits/stdc++.h>
const long long mod = 5000011;
long long ans, n, k;
long long jc[mod];
long long exgcd(long long, long long, long long &, long long &);
long long inv(long long);
long long C(long long, long long);
int main() {
	scanf("%lld %lld", &n, &k);
	jc[0] = 1;
	for (int i = 1; i < mod; ++i) {
		jc[i] = jc[i - 1] * i % mod;
	}
	for (int i = 0; i * (k + 1) - k <= n; ++i) {
		(ans += C(n - (i - 1) * k, i)) %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}
inline long long exgcd(long long a, long long b,
	long long &x, long long &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	int tmp = exgcd(b, a % b, x, y);
	std::swap(x, y);
	y = y - x * (a / b);
	return tmp;
}
inline long long inv(long long a) {
	long long x, y;
	exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}
inline long long C(long long m, long long n) {
	return jc[m] * inv(jc[m - n] * jc[n] % mod) % mod;
}
