#include <bits/stdc++.h>
const int B = 2;
const int N = 300;
const int Np = N + 5;
const int mod = 998244353;
int n, a, b, c;
int dp[Np][Np][Np][B][B];
int main() {
    std::cin >> n >> a >> b >> c;
    register char l, o;
    register int i, j, k, s;
    dp[0][0][0][0][0] = 1;
    for (i = 0; i <= a; ++i) {
        for (j = 0; j <= b; ++j) {
            for (k = 0; k <= c; ++k) {
                for (l = 0; l < B; ++l) {
                    for (o = 0; o < B; ++o) {
                        s = dp[i][j][k][l][o];
                        if (!l) {
                            (dp[i + 1][j][k][0][0] += s) %= mod;
                        }
                        if (!o) {
                            (dp[i][j + 1][k][!l][0] += s) %= mod;
                        }
                        (dp[i][j][k + 1][o ^ l][!l] += s) %= mod;
                    }
                }
            }
        }
    }
    std::cout << dp[a][b][c][0][0] << std::endl;
    return 0;
}