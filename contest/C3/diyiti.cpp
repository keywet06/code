#include <bits/stdc++.h>

#define pub push_back

const int N = 100005;

int n, m, q, x, y, v;
int ifed[N], bled[N];

std::vector<int> to[N];

std::set<int> dang;
std::set<int> from[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> q;
    for (int i = 1; i < n; ++i) std::cin >> x >> y, to[x].pub(y), to[y].pub(x);
    for (int i = 0; i < m; ++i) std::cin >> x, ifed[x] = 1;
    for (int i = 1; i <= n; ++i) {
        if (!ifed[i]) continue;
        for (int j = 0; j < to[i].size() && (v = to[i][j]); ++j) {
            if (!ifed[v]) dang.insert(v), from[v].insert(i);
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> y;
        if (y < 4) std::cin >> x;
        if (y == 1) {
            if (!ifed[x]) {
                if (dang.find(x) != dang.end()) dang.erase(x);
                bled[x] = 1;
                continue;
            }
            
        }
    }
    return 0;
}