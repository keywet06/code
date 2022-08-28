#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using uint64 = unsigned long long;

const int A = 6;
const int B = 16;
const int AB = A * B;
const int N = 405;
const int K = 205;

int n, k;
int s[N], a[N], c[N], Lim[N], Sum[N], Num[N], Mod[N];

uint64 Ans;
uint64 d[A][AB];
uint64 f[K][A], g[K][A];

std::string Str;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> k;
    std::cin >> Str;
    for (int i = 0; i < n; ++i) s[n - 1 - i] = Str[i] >= 'A' ? Str[i] - 'A' + 10 : Str[i] - '0';
    for (int i = 0; i < n; ++i) a[i + k] += s[i], a[i] -= s[i];
    for (int i = 0; i < n + k; ++i) {
        if (a[i] < 0) a[i] += B, --a[i + 1];
    }
    n += k, d[0][0] = 1;
    int S = (n - 1) / k + 1;
    for (int i = 0; i < S; ++i) {
        for (int a = 0; a < B; ++a) {
            for (int j = 0; j <= (B - 1) * i; ++j) d[i + 1][a + j] += d[i][j];
        }
    }
    for (int q = 1; q <= S; ++q) {
        ++Lim[k], --Lim[0];
        for (int c = 0; Lim[c] < 0; ++c) Lim[c] += B, --Lim[c + 1];
        memset(Num, 0, sizeof(Num));
        memset(Sum, 0, sizeof(Sum));
        for (int p = S * k - 1; p >= n; --p) ++Num[p % k];
        for (int p = n - 1; p >= 0; --p) {
            ++Num[p % k];
            for (int e = 0, eLim = a[p]; e < eLim; ++e) {
                memset(f, 0, sizeof(f));
                memset(g, 0, sizeof(g));
                g[0][0] = 1;
                for (int i = 0; i < k; ++i) {
                    for (int j = 0; j < S; ++j) {
                        int c = Lim[i] - j - Sum[i], t = S - Num[i], r = t * (B - 1);
                        c = (c + S * B) % B;
                        for (int a = c; a <= r; a += B) {
                            f[i + 1][(a + j + Sum[i]) / B] += (f[i][j] + g[i][j] * (a + Sum[i])) * d[t][a];
                            g[i + 1][(a + j + Sum[i]) / B] += g[i][j] * d[t][a];
                        }
                    }
                }
                Ans += f[k][Lim[k]];
                ++Sum[p % k];
            }
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}