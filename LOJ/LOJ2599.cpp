#include <bits/stdc++.h>
const int mod = 10007;
int a, b, k, m, n;
int jc[mod];
int power(int, int);
int exgcd(int, int, int &, int &);
int inv(int);
int C(int, int);
/*
 * write $C_{k}^{n} \times a^n \times b^m$
 */
int main() {
	scanf("%d %d %d %d %d", &a, &b, &k, &n, &m);
	a %= mod;
	b %= mod;
	jc[0] = 1;
	for (int i = 1; i < mod; ++i) {
		jc[i] = jc[i - 1] * i % mod;
	}
	printf("%d\n", C(k, n) * power(a, n) % mod * power(b, m) % mod);
	return 0;
}
/*
 * return $x^y$
 */
inline int power(int x, int y) {
	return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
inline int exgcd(int a, int b, int &x, int &y) {
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
inline int inv(int a) {
	int x, y;
	exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}
inline int C(int m, int n) {
	return jc[m] * inv(jc[m - n] * jc[n] % mod) % mod;
}
