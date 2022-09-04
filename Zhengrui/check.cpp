#include <bits/stdc++.h>

const int N = 240;
const int M = 1000005;

int p, q;
int a[N], qs[M];

int d[255];

int main() {
    for (int i = 0; i <= 9; ++i) d['0' + i] = i;
    for (int i = 0; i <= 6; ++i) d['A' + i] = i + 10;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> p >> q;
    for (int i = 0; i < N; ++i) std::cin >> a[i];
    for (int i = 0; i < q; ++i) std::cin >> qs[i];
    for (int i = 0; i < q; ++i) {
        std::string s;
        std::cin >> s;
        int S = 0;
        for (int j = 0; j < N / 4; ++j) {
            int c = (N / 4 - j - 1) * 4, x = d[s[j]];
            if (x & 1) S = (S += a[c + 0]) >= p ? S - p : S;
            if (x & 2) S = (S += a[c + 1]) >= p ? S - p : S;
            if (x & 4) S = (S += a[c + 2]) >= p ? S - p : S;
            if (x & 8) S = (S += a[c + 3]) >= p ? S - p : S;
        }
        if (S != qs[i])
            std::cout << "Wrong Answer on test #" << i << ": yours is " << S << ", answer is " << qs[i] << '\n';
    }
    return 0;
}