#include <bits/stdc++.h>
const int n_MAX = 1000005;
int n, num, x;
int a[n_MAX], cc[n_MAX];
int main() {
	freopen("in.in", "r", stdin);
	while (scanf("%d", &n) != EOF) {
		if (n == 0) return 0;
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		num = 0;
		for (int i = 1; i <= n; ++i) num += a[i];
		num /= n;
		cc[0] = 0;
		for (int i = 1; i < n; ++i) cc[i] = cc[i - 1] + a[i] - num;
		std::nth_element(cc, cc + n / 2, cc + n);
		x = -cc[n / 2];
		num = 0;
		for (int i = 0; i < n; ++i) num += std::abs(x + cc[i]);
		printf("%d\n", num);
		n = 0;
	}
	return 0;
}
