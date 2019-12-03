#include <bits/stdc++.h>
const int N = 1005;
int id, max, n, t, tmp;
int r[N];
int main() {
    freopen("icow.in", "r", stdin);
    freopen("icow.out", "w", stdout);
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &r[i]);
    }
    for (int i = 1; i <= t; ++i) {
        max = 0;
        id = 0;
        for (int j = 1; j <= n; ++j) {
            if (r[j] > max) {
                max = r[j];
                id = j;
            }
        }
        tmp = max % (n - 1);
        for (int j = 1; j <= tmp + (id <= tmp); ++j) {
            ++r[j];
        }
        tmp = max / (n - 1);
        for (int j = 1; j <= n; ++j) {
            r[j] += tmp;
        }
        r[id] = 0;
        printf("%d\n", id);
    }
    return 0;
}