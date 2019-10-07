#include <bits/stdc++.h>
const int N = 131072;
const int N2 = 65536;
const int M = 64;
int now = 3, T, n, x, y, z, w, ans;
int a[N + 1], b[N + 1];
int main() {
    a[0] = 1;
    a[3] = 1;
    b[3] = b[4] = b[5] = 1;
    for (int i = 6; i <= N; ++i) {
        if (i > (1 << now)) {
            ++now;
        }
        a[i] = 1 - a[(1 << now) - i];
        b[i] = b[i - 1] + a[i];
    }
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        x = (n + N - 1) / N;
        y = (n - 1) % N + 1;
        printf("%d\n", b[y] + b[x - 1] + (x - 1) * (N2 - 1) + (n + N2) / (262144));
    }
    return 0;
}