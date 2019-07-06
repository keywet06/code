#include <bits/stdc++.h>
class node {
    public:
        int t, f, h;
};
const int N = 1005;
int d, dpmax, g;
int dp[N];
node a[N];
int oper(node, node);
int main() {
    scanf("%d %d", &d, &g);
    for (int i = 1; i <= g; ++i) {
        scanf("%d %d %d", &a[i].t, &a[i].f, &a[i].h);
    }
    std::sort(a + 1, a + g + 1, oper);
    dp[0] = 10;
    dpmax = 10;
    for (int i = 1; i <= g; ++i) {
        for (int j = 0; j <= d; ++j) {
            dp[j] += a[i].f;
        }
        dpmax += a[i].f;
    }
    return 0;
}
inline int oper(node a, node b) {
    return a.t < b.t;
}