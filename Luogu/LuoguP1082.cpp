#include <bits/stdc++.h>
long long a, b, x, y;
long long exgcd(long long, long long, long long&, long long&);
int main() {
	scanf("%lld %lld", &a, &b);
	a %= b;
	exgcd(a, b, x, y);
	while (x <= 0) x += b;
	printf("%lld\n", x);
	return 0;
}
long long exgcd(long long a, long long b, long long &x, long long &y) {
	if (b != 0) {
		exgcd(b, a % b, y, x);
		y -= (a / b) * x;
	} else {
		x = 1ll;
		y = 0ll;
	}
}
