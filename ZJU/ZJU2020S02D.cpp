#include <bits/stdc++.h>
const int N = 5000005;
int p[N], k[N];
long long T, n, m, cnt, l, r, t, q;
long long s[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    for (int i = 2; i < N; ++i) {
        if (!k[i]) {
            k[i] = 1;
            p[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * p[j] < N; ++j) {
            k[i * p[j]] = p[j];
            if (i % p[j] == 0) break;
        }
    }
    s[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (k[i] == 1) {
            s[i] = i - 1;
            continue;
        }
        t = i;
        q = k[i];
        t /= q;
        l = q - 1;
        while (t % q == 0) {
            t /= q;
            l *= q;
        }
        s[i] = l * s[t];
    }
    for (int i = 2; i < N; ++i) s[i] += s[i - 1];
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m;
        --m;
        if (n == m) {
            std::cout << "3\n";
            continue;
        }
        if (!m) {
            std::cout << "1\n";
            continue;
        }
        l = n / (m + 1) + 1;
        r = n / m;
        if (l > r) {
            std::cout << "0\n";
            continue;
        }
        std::cout << 2 * (s[r] - s[l - 1]) << '\n';
    }
    return 0;
}