#include <bits/stdc++.h>
const int N = 25;
int ans, m, n;
int a[N];
void dfs(int, int);
void dp();
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}
inline void dfs(int x, int y) {
    if (y > m) {
        return;
    }
    if (x > n) {
        dp();
    }

}
