#include <cstdio>
#include <algorithm>
int ans, n, now, r;
int a[10005];
int main() {
	scanf("%d %d", &r, &n);
	while (r + n > -2) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		std::sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; ++i) {
			if (now + r < a[i]) {
				++ans;
				now = a[i] + r;
			}
		}
		printf("%d\n", ans);
		scanf("%d %d", &r, &n);
	}
	return 0;
}