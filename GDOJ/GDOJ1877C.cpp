#include <bits/stdc++.h>

const int C = 30;
const int N = 1000001;

int n, x, S, Tn;

int Min[N];
int ac[C][N], fc[C][N], sc[C];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    n = 21;
    for (int i = 0; i <= n; ++i) {
        int *a = ac[i], *f = fc[i];
        a[0] = 1, S = 0;
        for (int j = 1; j <= n; ++j) {
            x = j <= i ? 2 : 1;
            for (int i = S; i >= 0; --i) a[i + x] += a[i];    
            S += x;
        }
        for (int i = 1; i < N; ++i) f[i] = i;
        for (int i = 1; i << 1 < S; ++i) {
            for (int j = a[i]; j < N; ++j) f[j] = std::min(f[j], f[j - a[i]] + 1);
        }
        sc[i] = S;
    }
    int T;
    std::cin >> T;
    while (T--) {
        int k;
        std::cin >> k;
        int t, *a, *f, S;
        for (int i = 0; i <= n; ++i) {
            if (fc[i][k - 1] + n <= C) {
                t = i, a = ac[i], f = fc[i], S = sc[i];
                break;
            }
        }
        int Now = k - 1;
        std::cout << f[Now] + n << '\n';
        for (int i = 1; i <= n; ++i) std::cout << (i <= t ? 2 : 1) << ' ';
        while (Now) {
            while (Now - a[S] < 0 || f[Now - a[S]] + 1 != f[Now]) --S;
            std::cout << -S << ' ', Now -= a[S];
        }
        std::cout << '\n';
    }
    return 0;
}