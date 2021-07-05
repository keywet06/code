#include <bits/stdc++.h>

const int N = 4;

char e[N];

int T, n, t, p;
int a[N], b[N], c[N], f[N];
int d[N][N];

std::string s;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    e[0] == 'A', e[1] = 'T', e[2] = 'O', e[3] = 'N';
    memset(d, 0, sizeof(d));
    while (T--) {
        std::cin >> s, n = s.length();
        a[0] = a[1] = a[2] = a[3] = 0;
        b[0] = 0, b[1] = 1, b[2] = 2, b[3] = 3;
        for (int i = 0; i < n; ++i) {
            if (s[i] == e[0]) ++a[0];
            if (s[i] == e[1]) ++a[1];
            if (s[i] == e[2]) ++a[2];
            if (s[i] == e[3]) ++a[3];
        }
        std::sort(b, b + N, [](int x, int y) { return a[x] > a[y]; });
        for (int i = 0; i < N; ++i) f[b[i]] = i, c[i] = a[b[i]];
        if (c[0] > (c[1] + c[2] + c[3]) / 2) {
            t = c[0] - (c[1] + c[2] + c[3]) / 2;
            c[0] = (c[1] + c[2] + c[3]) / 2;
        }
        p = c[0] - c[1];
        d[0][2] += p, d[2][3] += p, d[3][0] += p;
        p = c[0] - c[2];
        d[0][1] += p, d[1][3] += p, d[3][0] += p;
        p = c[0] - c[3];
        d[0][1] += p, d[1][2] += p, d[2][0] += p;
        p = c[1] + c[2] + c[3] - 2 * c[0];
        d[0][1]
    }
    return 0;
}