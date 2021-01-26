#include <bits/stdc++.h>

const int N = 7;

int a[N];

int main() {
    for (int i = 0; i < N; ++i) std::cin >> a[i];
    std::sort(a, a + N);
    std::cout << a[0] << ' ' << a[1] << ' ' << a[6] - a[0] - a[1] << std::endl;
    return 0;
}