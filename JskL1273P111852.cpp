#include <bits/stdc++.h>
const int n_MAX = 1000005;
char ch;
int cnt, m, n, x, y;
int ans[n_MAX], father[n_MAX], head[n_MAX], next[n_MAX], now[n_MAX];
int to[n_MAX];
void insert(int, int);
int ren(int);
void bec(int);
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y);
		father[y] = x;
	}
	for (int i = 1; i <= n; ++i) now[i] = 1;
	ren(1);
	for (int i = 1; i <= m; ++i) {
		getchar();
		scanf("%c %d", &ch, &y);
		if (ch == 'C') bec(y);
		if (ch == 'Q') printf("%d\n", ans[y]);
	}
	return 0;
}
inline void insert(int x, int y) {
	++cnt;
	next[cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
}
inline int ren(int x) {
	for (int u = head[x]; u; u = next[u]) ans[x] += ren(to[u]);
	return ++ans[x];
}
inline void bec(int u) {
	x = 1 - (now[u] << 1);
	now[u] = 1 - now[u];
	while (u) {
		ans[u] += x;
		u = father[u]; 
	}
}
