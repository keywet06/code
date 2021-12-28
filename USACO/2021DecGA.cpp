#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

const int N = 100005;

int T, n, k, LastI, Ans;
int a[N], b[N], f[N], g[N];

inline int Solve(int *a, int *b, int n) {
    a[0] = -1e9, b[0] = 0;
    if (T == 1) {
        if (n % 2 == 0) return 0;
        int Ret = 2e9;
        for (int i = 1; i <= n; ++i) {
            if (i & 1 || a[i + 1] - a[i - 1] <= k) Mid(Ret, b[i]);
        }
        return Ret;
    }
    memset(f, 192, sizeof(int) * (n + 5));
    memset(g, 192, sizeof(int) * (n + 5));
    f[0] = 0;
    int fp0 = 2, fp1 = 1, gp0 = 2, gp1 = 1, fm0, fm1, gm0, gm1;
    fm0 = 0, fm1 = gm0 = gm1 = -int(1e9) - 5;
    for (int i = 1; i <= n; ++i) {
        while (fp0 <= n && a[fp0] + k < a[i]) Mad(fm0, f[fp0]), fp0 += 2;
        while (fp1 <= n && a[fp1] + k < a[i]) Mad(fm1, f[fp1]), fp1 += 2;
        while (gp0 <= n && a[gp0] + k < a[i]) Mad(gm0, g[gp0]), gp0 += 2;
        while (gp1 <= n && a[gp1] + k < a[i]) Mad(gm1, g[gp1]), gp1 += 2;
        if (i & 1) {
            f[i] = std::max(fm0, gm1) + b[i];
            if (i == n || a[i + 1] - a[i - 1] > k) continue;
            g[i] = std::max(fm1, gm0) + b[i];
        } else {
            f[i] = std::max(fm1, gm0) + b[i];
            if (i == n || a[i + 1] - a[i - 1] > k) continue;
            g[i] = std::max(fm0, gm1) + b[i];
        }
    }
    while (fp0 <= n) Mad(fm0, f[fp0]), fp0 += 2;
    while (fp1 <= n) Mad(fm1, f[fp1]), fp1 += 2;
    while (gp0 <= n) Mad(gm0, g[gp0]), gp0 += 2;
    while (gp1 <= n) Mad(gm1, g[gp1]), gp1 += 2;
    return n & 1 ? std::max(fm1, gm0) : std::max(fm0, gm1);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i] >> b[i];
    a[n + 1] = int(2e9) + 5;
    for (int i = 2; i <= n + 1; ++i) {
        if (a[i] - a[i - 1] <= k) continue;
        Ans += Solve(a + LastI, b + LastI, i - 1 - LastI), LastI = i - 1;
    }
    std::cout << Ans << std::endl;
    return 0;
}