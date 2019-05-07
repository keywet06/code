#include <bits/stdc++.h>
const int n_MAX = 200000;
const int int_MAX = 2147483647;
int n, i, dfs, min = int_MAX;
int a[n_MAX + 1], f[n_MAX + 1], c[n_MAX + 1];
int find(int);
int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= n; ++i) min = std::min(min, find(i));
    printf("%d\n", min);
    return 0;
}
int find(int x) {
    if (f[x]) return f[x];
    c[x] = ++dfs;
    if (c[a[x]])
        f[x] = c[x] - c[a[x]] + 1;
    else
        f[x] = find(a[x]);
    return f[x];
}
