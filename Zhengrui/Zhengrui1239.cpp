#include <bits/stdc++.h>
const int N = 100000;
const int Np = N + 5;
int n, x, s;
int a[Np];
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        ++a[x];
    }
    x = 0;
    for (int i = 0; i <= N; ++i) {
        x += a[i];
        if (x >= (n + 1) / 2) {
            x = i;
            break;
        }
    }
    s = 0;
    for (int i = 0; i <= N; ++i) {
        s += a[i] * std::abs(x - i);
    }
    std::cout << s << std::endl;
    return 0;
}