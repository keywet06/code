#include <bits/stdc++.h>

struct TInt {
    std::map<int, int> Map;
    TInt() {}
    TInt(int n) {
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) n /= i, ++Map[i--];
        }
        if (n != 1) ++Map[n];
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n, Ia, Ib;
    std::cin >> n >> Ia >> Ib;
    TInt Ma(Ia), Mb(Ib);
    for (int i = 1; i < n; ++i) {
        std::cin >> Ia >> Ib;
        TInt a(Ia), b(Ib);
        std::map<int, std::pair<int, int> > Map;
        for (auto [x, y] : a.Map) Map[x].first += y;
        for (auto [x, y] : b.Map) Map[x].second += y;
        // 
        for (auto [x, p] : Map) {
            auto [A, B] = p;

        }
    }
    return 0;
}
