#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    int x = 1;
    while (x < n && a[x - 1] < a[x]) ++x;
    std::cout << a[x - 1] << std::endl;
    return 0;
}