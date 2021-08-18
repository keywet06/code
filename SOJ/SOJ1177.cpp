#include <bits/stdc++.h>

using pair = std::pair<int, int>;

const int N = 1005;

int n, m, q, o, x, y, z;
int ta[N], tb[N];

std::set<int> set[N];

inline void andset(int cx, int cy, int cz) {
    int ca = 0, cb = 0, c1 = 0, c2 = 0;
    for (int i : set[cx]) ta[++ca] = i;
    for (int i : set[cy]) tb[++cb] = i;
    set[cz].clear();
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> q;
    for (int iq = 1; iq <= q; ++iq) {
        std::cin >> o;
        if (o == 1) {
            std::cin >> x >> y;
        } else if (o == 2) {
            std::cin >> x;
        }
    }
    return 0;
}