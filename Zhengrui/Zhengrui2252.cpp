#include <bits/stdc++.h>

using int64 = long long;

const int N = 1000005;

int n;
int a[N];

int64 m;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    
    return 0;
}