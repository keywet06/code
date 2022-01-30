#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int> > a(n);
    for (auto &x : a) std::cin >> x.first >> x.second;
    std::sort(a.begin(), a.end());
    
    return 0;
}
