#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int C = 2;
const int N = 200005;
const int mod = 998244353;
int n, maxa, maxb, now, num;
int a[N], b[N], s[N];
int f[C][N];
std::vector<int> o[N];
int mo(int x) { return x >= mod ? x - mod : x; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    num = n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i] >> b[i];
        maxa = std::max(maxa, a[i]);
        o[a[i] + b[i]].push_back(a[i]);
    }
    for (int i = 2 * n - 2; i >= 0; i--) {
        now = 1 - now;
        int l = i - n + 1 > 0 ? i - n + 1 : 0, r = n < i ? n : i;
        for (int j = l; j <= r; j++) {
            f[now][num + j] = mo(f[1 - now][num + j] + f[1 - now][num + j + 1]);
        }
        for (int j = 0; j < o[i].size(); j++) {
            f[now][num + o[i][j]] = mo(f[now][num + o[i][j]] + 1);
        }
        f[now][num + l - 1] = f[now][num + l - 2] = f[1 - now][r + 1] =
            f[1 - now][r + 2] = 0;
        if (i < n) s[i] = f[now][num];
    }
    for (int i = 0; i < n; i++) std::cout << s[i] << ' ';
    std::cout << std::endl;
    return 0;
}