#include <bits/stdc++.h>
const int N = 1000005;
int n;
int r[N];
long long ans, a, b, c;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> r[i];
    std::cin >> a >> b >> c;
    for (int i = 1; i <= n; ++i) {
        ans += -a * r[i] * r[i] + b * r[i] + c;
    }
    std::cout << ans << std::endl;
    return 0;
}