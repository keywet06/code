#include <bits/stdc++.h>

const int C = 30;
const int N = 1000001;

int n, x, S;

int a[N], dp[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    a[0] = 1;
    while (n--) {
        std::cin >> x;
        for (int i = S; i >= 0; --i) a[i + x] += a[i];
        S += x;
    }
    for (int i = 0; i <= S; ++i) std::cout << a[i] << " \n"[i == S];
    return 0;
}