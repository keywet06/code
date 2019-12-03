#include <bits/stdc++.h>
int n;
int a[501], dp[501][501];
long long ans, max;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		a[i + n] = a[i];
	}
	for (int i = 2; i <= n << 1; ++i) {
		for (int j = i - 1; i - j < n && j >= 1; --j) {
			for (int k = j; k < i; ++k) dp[j][i] = std::max(dp[j][i], dp[j][k] + dp[k + 1][i] + a[i + 1] * a[k + 1] * a[j]);
			if (dp[j][i] > max) max = dp[j][i];
		}
	}
	printf("%lld", max);
	return 0;
} 
