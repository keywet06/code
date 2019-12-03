#include <bits/stdc++.h>
const int m_MAX = 20005;
const int n_MAX = 10005;
int a, b, c, cnt, m;
int n, op;
int next[m_MAX], to[m_MAX], val[m_MAX];
int dis[n_MAX], head[n_MAX], sta[n_MAX], su[n_MAX];
void insert(int, int, int);
int SPFA(int);
int main() {
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) dis[i] = -1e8;
    for (int i = 1; i <= m; ++i) {
		scanf("%d", &op);
        if (op == 1) {
			scanf("%d %d %d", &a, &b, &c);
            insert(b, a, c);
        } else if (op == 2) {
            scanf("%d %d %d", &a, &b, &c);
            insert(a, b, -c);
        } else {
            scanf("%d %d", &a, &b);
            insert(a, b, 0);
            insert(b, a, 0);
        }
    }
    for (int i = 1; i <= n; ++i) insert(0, i, 0);
    if (SPFA(0)) puts("Yes");
    else puts("No");
    return 0;
}
inline void insert(int a, int b, int c) {
	++cnt;
	next[cnt] = head[a];
	head[a] = cnt;
	to[cnt] = b;
	val[cnt] = c;
}
inline int SPFA(int s) {
	std::queue<int> q;
	q.push(s);
	sta[s] = 1;
	dis[s] = 0;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		sta[a] = 0;
		for (int u = head[a]; u; u = next[u]) 
			if (dis[a] + val[u] > dis[to[u]]) {
				dis[to[u]] = dis[a] + val[u];
				++su[to[u]];
				if (su[to[u]] > n) return 0;
				if (!sta[to[u]]) {
					sta[to[u]] = 1;
					q.push(to[u]);
				}
			}
	}
	return 1;
}
