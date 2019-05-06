#include <bits/stdc++.h>
const int M = 2005;
const int N = 25;
int ans, m, n, sum, tmp;
int a[N], b[N];
int f[M];
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
    printf("Debug: dfs(int x = %d, int y = %d);\n", x, y);
    if (y > m) {
        return;
    }
    if (x > n) {
        if (y == m) {
            dp();
        }
        return;
    }
    b[x] = 1;
    dfs(x + 1, y + 1);
    b[x] = 0;
    dfs(x + 1, y);
}
inline void dp() {
    memset(f, 0, sizeof(f));
    sum = 0;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (b[i]) {
            continue;
        }
        sum += a[i];
        printf("Debug:i = %d; sum = %d;\n", i, sum);
        for (int j = sum; j >= a[i]; --j) {
            f[j] &= f[j - a[i]];
        }
    }
    tmp = 0;
    for (int i = 1; i <= sum; ++i) {
        tmp += f[i];
    }
    if (tmp > ans) {
        ans = tmp;
    }
}
