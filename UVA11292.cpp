#include <bits/stdc++.h>
const int m_MAX = 20000;
const int n_MAX = 20000;
int ans, flag, m, n, now;
int b[m_MAX];
int a[n_MAX];
int main() {
	scanf("%d %d", &n, &m);
	while (n || m) {
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= m; ++i) scanf("%d", &b[i]);
		std::sort(a + 1, a + n + 1);
		std::sort(b + 1, b + m + 1);
		now = 1;
		ans = flag = 0;
		for (int i = 1; i <= n; ++i) {
			while (now <= m && b[now] < a[i]) ++now;
			if (now > m) {
				flag = 1;
				break;
			}
			ans += b[now];
			++now;
		}
		if (flag) puts("Loowater is doomed!");
		else printf("%d\n", ans);
		scanf("%d %d", &n, &m);
	}
	return 0;
}
