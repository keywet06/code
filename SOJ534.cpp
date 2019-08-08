#include <bits/stdc++.h>
const int N = 500005;
char opt;
int cnt, n, q;
int a[N], b[N];
int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[++cnt] = a[i];
    }
    for (int i = 1; i <= q; ++i) {
        scanf("\n%c", &opt);
        if (opt == 'M') {
            op[i] = 1;
            scanf("%d %d %d", &l[i], &r[i], &y[i]);
            b[++cnt] = y[i];
        } else {
            op[i] = 2;
            scanf("%d", &
        }
    }
    return 0;
}
