#include <bits/stdc++.h>

using int64 = long long;

const int S = 10000000;
const int N = 10000005;

int PriCnt;
int Vis[N], Pri[N], Ter[N];

int64 l, r, k;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> l >> r >> k;
    for (int i = 2; i < N; ++i) {
        if (!Ter[i]) Pri[++PriCnt] = i;
        for (int j = 1; j <= PriCnt && i * Pri[j] < N; ++j) {
            Ter[i * Pri[j]] = Pri[j];
            if (i % Pri[j] == 0) break;
        }
    }
    for (int i = 2; i <= k && i <= S; ++i) {
        if (Ter[i]) continue;
        for (int64 j = std::max((l - 1) / i + 1, 2ll) * i; j <= r; j += i) Vis[j - l] = 1;
    }
    int64 Ans = 0;
    for (int64 i = l; i <= r; ++i)  {
        if (!Vis[i - l]) Ans ^= i;
    }
    std::cout << Ans << '\n';
    return 0;
}