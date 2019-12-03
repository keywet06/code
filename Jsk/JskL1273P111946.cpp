#include <bits/stdc++.h>
const int h_MAX = 200005;
int h, m, n, w, x;
int ans[h_MAX], left[h_MAX], middle[h_MAX], right[h_MAX];
void build(int, int, int);
void redata(int);
int main() {
    scanf("%d %d %d", &h, &w, &n);
    h = std::min(h, n);
    build(1, 1, h);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
    	if (ans[1] < x) puts("-1");
        else redata(1);
    }
    return 0;
}
inline void build(int u, int l, int r) {
    left[u] = l;
    right[u] = r;
    middle[u] = (l + r) >> 1;
	ans[u] = w;
    if (l < r) {
        build(u << 1, l, middle[u]);
        build(u << 1 | 1, middle[u] + 1, r);
    }
}
inline void redata(int u) {
    if (left[u] == right[u]) {
        ans[u] -= x;
        printf("%d\n", left[u]);
        return;
    }
    if (ans[u << 1] >= x) redata(u << 1);
    else redata(u << 1 | 1);
    ans[u] = std::max(ans[u << 1], ans[u << 1 | 1]);
} 
