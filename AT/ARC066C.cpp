#include <bits/stdc++.h>

using int64 = long long;

const int B = 3;
const int N = 100005;

int n;
int a[N], b[N], d[N];

int64 f[N][B];

int getc() {
    int x = getchar();
    while (x != '-' && x != '+') x = getchar();
    return x == '-';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> a[1];
    for (int i = 2; i <= n; ++i) {
        b[i] = getc(), std::cin >> a[i], d[i] = (b[i] ? -a[i] : a[i]);
    }
    memset(f, 128, sizeof(f));
    f[1][0] = b[1];
    for (int i = 2; i <= n; ++i) {
        f[i][0] = std::max(f[i - 1][0] + d[i], f[i - 1][1] + d[i]);
        f[i][1] = std::max(f[i - 1][0] + d[i], f[i - 1][1] - d[i]);
        f[i][2] = std::max(std::max(f[i - 1][0] + d[i], f[i - 1][1] - d[i]),
                           f[i - 1][2] + d[i]);
        if (b[i]) {
            f[i][1] = std::max(f[i][1], f[i - 1][0] + d[i]);
            f[i][2] = std::max(f[i][2], f[i - 1][1] + d[i]);
        }
    }
    
    std::cout << f[n][0] << std::endl;
    return 0;
}