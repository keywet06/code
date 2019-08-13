#include <bits/stdc++.h>
const int N = 200005;
int m, n, x, y, z;
int a[N], b[N], k[N], op[N], t[N];
std::priority_queue<int, std::vector<int>, std::greater<int> > pq[N];
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d %d %d", &a[i], &b[i], &k[i], &op[i], &t[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &x);
        for (y = 1; y; y = (x <= k[y] ? a[y] : b[y])) {
            if (op[y] == 1) {
                x |= t[y];
            } else if (op[y] == 2) {
                x ^= t[y];
            } else {
                x &= t[y];
            }
            z = y;
        }
        pq[z].push(x);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d", (int)(pq[i].size()));
        while (!pq[i].empty()) {
            printf(" %d", pq[i].top());
            pq[i].pop();
        }
        printf("\n");
    }
    return 0;
}