#include <bits/stdc++.h>

using int64 = long long;

const int N = (int)(2e7) + 5;

char a[N], b[N];

int n, m, l, r;
int z[N], p[N];

int64 ansz, ansp;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> a >> b, n = strlen(a), m = strlen(b), a[n] = '!', b[m] = '@';
    ansz = m + 1;
    for (int i = 1; i < m; ++i) {
        z[i] = r < i ? 0 : std::min(z[i - l], r - i + 1);
        while (b[z[i]] == b[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i] - 1;
        ansz ^= int64(i + 1) * (z[i] + 1);
    }
    l = r = 0;
    for (int i = 0; i < n; ++i) {
        p[i] = r < i ? 0 : std::min(z[i - l], r - i + 1);
        while (b[p[i]] == a[i + p[i]]) ++p[i];
        if (i + p[i] > r) l = i, r = i + p[i] - 1;
        ansp ^= int64(i + 1) * (p[i] + 1);
    }
    std::cout << ansz << '\n';
    std::cout << ansp << '\n';
    return 0;
}