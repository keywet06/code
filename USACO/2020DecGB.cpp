#include <bits/stdc++.h>

using int64 = long long;

const int A = 3;
const int B = 5;
const int64 P = 1000000007;

int n;

int64 ans;
int64 a[A][B], b[A][B];

std::string s;

void r(int x) {
    b[0][x] = a[0][0] + a[0][1] + a[0][2] + a[0][3] + a[0][4] - a[0][x];
    b[1][x] = a[0][x] + a[1][x];
    b[2][x] = a[1][1] + a[1][2] + a[1][3] + a[1][4] - a[1][x] + a[2][1] +
              a[2][2] + a[2][3] + a[2][4] - a[2][x];
}

int main() {
    std::cin >> s, n = s.length(), a[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A' || s[i] == '?') r(1);
        if (s[i] == 'C' || s[i] == '?') r(2);
        if (s[i] == 'G' || s[i] == '?') r(3);
        if (s[i] == 'T' || s[i] == '?') r(4);
        for (int c = 0; c < A; ++c) {
            for (int d = 0; d < B; ++d) a[c][d] = b[c][d] % P, b[c][d] = 0;
        }
    }
    for (int c = 0; c < A; ++c) {
        for (int d = 0; d < B; ++d) ans += a[c][d];
    }
    std::cout << ans << std::endl;
    return 0;
}