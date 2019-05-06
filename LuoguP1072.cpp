#include <bits/stdc++.h>
const int cnt_MAX = 100;
int T, a0, a1, b0, b1, cnt, xmax, xmin;
int a0p[cnt_MAX], a1p[cnt_MAX], b0p[cnt_MAX], b1p[cnt_MAX], p[cnt_MAX];
long long ans = 1;
void Main();
int main() {
	scanf("%d", &T);
	while (T--) {
		Main();
		cnt = 0;
		memset(p, 0, sizeof(p));
		memset(a0p, 0, sizeof(a0p));
		memset(a1p, 0, sizeof(a1p));
		memset(b0p, 0, sizeof(b0p));
		memset(b1p, 0, sizeof(b1p));
		ans = 1;
	}
	return 0;
}
void Main() {
	scanf("%d %d %d %d", &a0, &a1, &b0, &b1);
	for (register int i = 2; i <= sqrt(b1); ++i)
		if (b1 % i == 0) {
			if (p[cnt] != i) p[++cnt] = i;
			++b1p[cnt];
			b1 /= i;
			--i;
		}
	if (p[cnt] != b1 && b1 != 1) p[++cnt] = b1;
	b1p[cnt] += b1 != 1;
	for (register int i = 1; i <= cnt; ++i) {
		while (b0 % p[i] == 0) {
			++b0p[i];
			b0 /= p[i];
		}
		while (a0 % p[i] == 0) {
			++a0p[i];
			a0 /= p[i];
		}
		while (a1 % p[i] == 0) {
			++a1p[i];
			a1 /= p[i];
		}
		xmax = b1p[i];
		xmin = a1p[i];
		if (a0p[i] > a1p[i]) xmax = a1p[i];
		if (b0p[i] < b1p[i]) xmin = b1p[i];
		if (xmax < xmin) {
		    puts("0");
			return;
		}
		ans *= xmax - xmin + 1;
	}
	printf("%lld\n", ans);
}
