#include <bits/stdc++.h>

using int64 = long long;

const int N = 4005;

int Cnt;
int Dis[N], Fa[N];

std::vector<int> Son[N];

int64 Ans;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    Cnt = 1;
    while (n--) {
        int o, x;
        std::cin >> o >> x;
        if (o == 1) {
            Son[x].push_back(++Cnt), Fa[Cnt] = x;
        } else {
            Dis[x] = INT_MAX, x = Fa[x];
        }
        while (x) {
            int D = INT_MAX;
            for (auto c : Son[x]) D = std::min(D, Dis[c]);
            D = D == INT_MAX ? 0 : D + 1;
            if (D == Dis[x]) break;
            Ans -= Dis[x], Ans += Dis[x] = D, x = Fa[x];
        }
        std::cout << Ans << '\n';
    }
    return 0;
}