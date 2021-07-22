#include <bits/stdc++.h>

const int N = 20;
const double exp = 1e-6;

int T;
int a, b, c;

double x, y, z, v;
double dp[N][N];

inline int divs(double x) {
    int a = 0;
    while (x >= exp) x -= v, ++ a;
    return a;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> x >> y >> z >> v, v /= 2;
        a = divs(x), b = divs(y);
        dp[0][0] = 1;
        for (int i = 1; i <= x; ++i) {
            dp[i][0] = dp[i - 1][0] *    + 1; 
        }
    }
    return 0;
}