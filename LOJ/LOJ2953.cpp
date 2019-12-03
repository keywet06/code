#include <bits/stdc++.h>
const int A = 5005;
int cnt, f, f2, m, n, x, y;
int ans[A], c[A], ex[A], ey[A];
int a[A][A];
std::priority_queue<int, std::vector<int>, std::greater<int> > pq[A];
void dfs1(int);
void dfs2(int);
int main() {
	scanf("%d %d", &n, &m);
	if (m == n - 1) {
		for (int i = 1; i <= m; ++i) {
			scanf("%d %d", &x, &y);
			a[x][y] = 1;
			a[y][x] = 1;
		}
		printf("1");
		dfs1(1);
	} else {
		for (int i = 1; i <= m; ++i) {
			scanf("%d %d", &ex[i], &ey[i]);
		}
		for (int i = 1; i <= n; ++i) {
			ans[i] = n + 1;
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (i != j) {
					pq[ex[j]].push(ey[j]);
					pq[ey[j]].push(ex[j]);
				}
			}
			for (int j = 1; j <= n; ++j) {
				c[j] = 0;
			}
			cnt = f = f2 = 0;
			dfs2(1);
			if (f2) {
				for (int i = 1; i <= n; ++i) {
					while (!pq[i].empty()) {
						pq[i].pop();
					}
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d ", ans[i]);
		}
	}
	return 0;
}
inline void dfs1(int x) {
	c[x] = 1;
	for (int i = 1; i <= n; ++i) {
		if (a[i][x] && !c[i]) {
			c[i] = 1;
			printf(" %d", i);
			dfs1(i);
		}
	}
}
inline void dfs2(int x) {
	c[x] = 1;
	++cnt;
	if (!f && ans[cnt] < x) {
		f2 = 1;
		return;
	}
	if (ans[cnt] > x) {
		f = 1;
	}
	ans[cnt] = x;
	while (!pq[x].empty()) {
		int u = pq[x].top();
		pq[x].pop();
		if (c[u]) {
			continue;
		}
		dfs2(u);
		if (f2) {
			return;
		}
	}
}
