#include <bits/stdc++.h>

using uint64 = unsigned long long;

const int B = 4;
const int N = 100005;

int n, s;
int c[B], d[B];

uint64 ans, e, h;
uint64 f[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    for (int i = 0; i < B; ++i) std::cin >> c[i];
    f[0] = 1;
    for (int i = 0; i < B; ++i) {
        for (int j = c[i]; j < N; ++j) f[j] += f[j - c[i]];
    }
    std::cin >> n;
    while (n--) {
        for (int i = 0; i < B; ++i) std::cin >> d[i];
        std::cin >> s;
        ans = 0;
        for (int i = 0; i < 1 << B; ++i) {
            e = h = 0;
            for (int j = 0; j < B; ++j) {
                if (i >> j & 1) ++e, h += c[j] * (d[j] + 1);
            }
            ans += (e & 1 ? -1 : 1) * (h <= s ? f[s - h] : 0);
        }
        std::cout << ans << '\n';
    }
    return 0;
}