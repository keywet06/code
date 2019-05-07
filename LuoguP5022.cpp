#include <bits/stdc++.h>
std::priority_queue<int,vector<int>,greater<int> > pq;
void insert(int, int);
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	pq.push(1);
	sta[1] = 1;
	printf("1 ");
	for (int i = 2; i <= n; ++i) {
		s = pq.pop();
	}
	return 0;
}
void insert(int a, int b) {
	++cnt;
	next[cnt] = head[a];
	head[a] = cnt;
	to[cnt] = b;
}
