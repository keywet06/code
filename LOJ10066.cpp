#include <bits/stdc++.h>
const int N = 305;
int n, x;
int dis[N], vis[N];
int ed[N][N];
int main() {
	scanf("%d", &n);
	memset(ed, 127, sizeof(ed));
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		ed[0][i] = ed[i][0] = x;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			
		}
	}
	return 0;
}
