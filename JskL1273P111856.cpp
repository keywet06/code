#include <bits/stdc++.h>
const int n_MAX = 50005;
long long ans, g, l, n, now, m, x, y;
long long a[n_MAX];
long long c3(long long);
long long gcd(long long, long long);
int main() {
	scanf("%lld %lld", &n, &m);
	if (m < 3){
		puts("0");
		return 0;
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%lld %lld", &x, &y);
		++a[x];
		--a[y + 1];
	}
	for (int i = 1; i <= n; ++i) {
		now += a[i];
		ans += c3(now);
	}
	l = c3(m);
	g = gcd(ans, l);
	if (g == l) printf("%lld\n", ans / l);
	else printf("%lld/%lld\n", ans / g, l / g);
	return 0;
}
inline long long c3(long long x) {return x * (x - 1) * (x - 2) / 6;}
inline long long gcd(long long x, long long y) {
	if (x % y == 0) return y;
	return gcd(y, x % y);
}
