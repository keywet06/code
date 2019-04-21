#include <bits/stdc++.h>
const int N = 45;
int n;
int a[N][N];
int main() {
    scanf("%d", &n);
    for (int i = 1, x = 1, y = (n + 1) >> 1; i <= n * n; ++i) {
        a[x][y] = i;
        if (x == 1 && y != n) {
            x = n;
            ++y;
        } else if (x != 1 && y == n) {
            --x;
            y = 1;
        } else if (x == 1 && y == n) {
            ++x;
        } else if (!a[x - 1][y + 1]) {
            --x;
            ++y;
        } else {
            ++x;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%d ", a[i][j]);
        }
        puts("");
    }
    return 0;
}