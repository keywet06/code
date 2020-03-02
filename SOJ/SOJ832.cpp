#include <bits/stdc++.h>
const int N = 100;
const int Np = N + 5;
int n;
int a[N];
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::cout << a[1] + a[2] << std::endl;
    std::cout << a[3] + a[2] << std::endl;
    std::cout << a[3] - a[2] << std::endl;
    return 0;
}