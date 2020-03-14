#include <bits/stdc++.h>
const long long M = 500005;
const long long N = 100005;
class node {
	public:
		long long dis, point;
		node(long long, long long);
};
long long cnt, n, m, x, y, z, s, t;
long long next[M], to[M], val[M];
long long head[N], dis[N], vis[N];
std::priority_queue<node, std::vector<node>, std::greater<node> > queue;
void insert(long long, long long, long long);
void addedge(long long, long long, long long);
long long operator > (node, node);
inline node::node(long long dis, long long point) {
	this->dis = dis;
	this->point = point;
}
inline void insert(long long x, long long y, long long z) {
	++cnt;
	next[cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	val[cnt] = z;
}
inline void addedge(long long x, long long y, long long z) {
	insert(x, y, z);
	insert(y, x, z);
}
inline long long operator > (node x, node y) {
	return x.dis > y.dis;
}
int main() {
	scanf("%lld %lld %lld %lld %lld", &n, &m, &x, &s, &t);
	for (long long i = 1; i <= m; ++i) {
		scanf("%lld %lld %lld", &x, &y, &z);
		insert(x, y, z);
	}
	for (long long i = 1; i <= n; ++i) {
		dis[i] = 1e15;
	}
	dis[s] = 0;
	queue.push(node(0, s));
	while (!queue.empty()) {
		node v = queue.top();
		queue.pop();
		if (vis[v.point]) {
			continue;
		}
		vis[v.point] = 1;
		for (long long u = head[v.point]; u; u = next[u]) {
			if (v.dis + val[u] < dis[to[u]]) {
				dis[to[u]] = v.dis + val[u];
				queue.push(node(dis[to[u]], to[u]));
			}
		}
	}
    printf("%lld\n", dis[t]);
	return 0;
}