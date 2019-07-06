#include <bits/stdc++.h>
int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d %d", &x, &y, &z, &w);
        addedge(x, y, z, w);
    }
    costflow();
    printf("%lld %lld")
    return 0;
}