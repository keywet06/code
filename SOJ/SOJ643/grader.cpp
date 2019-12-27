#include "match.h"
#include <bits/stdc++.h>

static const int N = 100005, LN = 20;
static int lc[N * LN], rc[N * LN], sum[N * LN], root[N + N], n, nn, idx, t, cnt;

static int insert(int root, int pos, int l = 0, int r = nn - 1) {
	int now = ++idx;
	sum[now] = sum[root] + 1, lc[now] = lc[root], rc[now] = rc[root];
	if (l == r) return now;
	int mid = l + r >> 1;
	if (pos <= mid) lc[now] = insert(lc[root], pos, l, mid);
	else rc[now] = insert(rc[root], pos, mid + 1, r);
	return now;
}
static int t_query(int root, int pos, int l = 0, int r = nn - 1) {
	if (l == pos || !root) return sum[root];
	int mid = l + r >> 1;
	if (pos <= mid) return sum[rc[root]] + t_query(lc[root], pos, l, mid);
	else return t_query(rc[root], pos, mid + 1, r);
}

int query(int l, int r) {
	if (l < 0 || r >= nn || l > r)
		printf("Invalid query %d %d\n", l, r), std::exit(0);
	if (++cnt > 10000000)
		printf("Query too many times."), std::exit(0);
	return t_query(root[r], l);
}

static int ans[N + N];
int main() {
	std::scanf("%d", &n), nn = n + n;
	for (int i = 0; i < nn; ++i) ans[i] = i ^ 1;//std::scanf("%d", ans + i);
	for (int i = 0; i < nn; ++i) {
		if (i) root[i] = root[i - 1];
		if (ans[i] < i) root[i] = insert(root[i], ans[i]);
	}
	std::vector<int> usr = match(n);
	if (usr.size() != nn)
		std::printf("Your answer's size must be %d.\n", nn), std::exit(0);
	for (int i = 0; i < nn; ++i)
		if (usr[i] != ans[i])
			std::printf("Wrong Answer."), std::exit(0);
	std::printf("%d\n", cnt);
	return 0;
}
