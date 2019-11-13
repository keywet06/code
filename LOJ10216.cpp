#include <bits/stdc++.h>
long long T, n, a, b, x, y, c, t;
long long gcd(long long, long long);
long long exgcd(long long, long long, long long &, long long &);
int main();
inline long long gcd(long long x, long long y) {
	return x % y ? gcd(y, x % y) : y;
}
inline long long exgcd(long long a, long long b,
	long long &x, long long &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	long long tmp = exgcd(b, a % b, x, y);
	std::swap(x, y);
	y = y - x * (a / b);
	return tmp;
}
int main() {
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld %lld %lld %lld", &n, &a, &x, &y);
		c = (y - x + n) % n;
		b = n;
		t = gcd(a, b);
		if (c % t) {
			printf("Impossible\n");
			continue;
		}
		a /= t;
		b /= t;
		c /= t;
		exgcd(a, b, x, y);
		x = (x * c % b + b) % b;
		printf("%lld\n", x);
	}
	return 0;
}
