#include <bits/stdc++.h>

using int64 = long long;

const int B = 2;
const int N = 5005;
const int P = 1000000007;

int n, x, na, nb;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> x, nb = x, na = n - x;
    int64 f[na + 1][nb + 1][B], g[na + 1][nb + 1][B];
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    f[0][0][1] = 1;
    for (int i = 0, I = -1; i <= na; ++i, ++I) {
        for (int j = 0, J = -1; j <= nb; ++j, ++J) {
            int64 &A = f[i][j][0], &B = f[i][j][1];
            int64 &C = g[i][j][0], &D = g[i][j][1];
            if (i) {
                A += i * f[I][j][0] + f[I][j][1];
                B += I * f[I][j][1];
                C += i * g[I][j][0] + g[I][j][1];
                D += I * g[I][j][1];
            }
            if (j) {
                A += J * f[i][J][0];
                B += j * f[i][J][1] + f[i][J][0];
                C += J * g[i][J][0];
                D += j * g[i][J][1] + g[i][J][0] + f[i][J][0];
            }
            A %= P, B %= P, C %= P, D %= P;
        }
    }
    std::cout << (g[na][nb][0] + g[na][nb][1]) % P << std::endl;
    return 0;
}