#include <bits/stdc++.h>

using int64 = long long;

const int P = 1000000007;
const int B = 2;
const int N = 4000;

int p, m, n = 1;

int64 a[N];
/* 
 * 表示 a 的前 i 位 p 进制数进了 j 次位
 * bool(k)[有数值限制], bool(l)[需要上一位进位] 的方案数
 */
int64 f[N][N][B][B];

std::string s;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> p >> m;
    std::cin >> s;
    for (char ch : s) {
        a[1] = a[1] * 10 + ch - '0';
        for (int i = 1; i < n; ++i) {
            a[i + 1] = a[i + 1] * 10 + a[i] / p, a[i] %= p;
        }
        while (a[n] >= p) a[n + 1] = a[n] / p, a[n++] %= p;
    }
    // f[n][0][1][0] = ;
    return 0;
}