#include <bits/stdc++.h>
const int n_MAX = 200005;
const int k_MAX = 55;
int n, k, p, ans, now;
int c[n_MAX], v[n_MAX];
int a[k_MAX][n_MAX], b[k_MAX][n_MAX];
int main() {
	scanf("%d %d %d", &n, &k, &p);
	for (int i = 1; i <= n; ++i) scanf("%d %d", &c[i], &v[i]);
	for (int i = 1; i <= n; ++i) ++c[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= k; ++j)
			a[j][i] = a[j][i - 1] + (c[i] == j);
	for (int i = n; i >= 1; --i)
		for (int j = 1; j <= k; ++j)
			b[j][i] = b[j][i + 1] + (c[i] == j);
	for (int i = 1; i <= n; ++i)
		if (v[i] <= p) {
			for (int j = 1; j <= k; ++j) ans += (a[j][i] - a[j][now]) * b[j][i];
			--ans;
			now = i;
		}
	printf("%d\n", ans);
	return 0;
}
