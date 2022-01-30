#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> Dis(n, q);
    std::vector<std::pair<std::pair<int, int>, int> > Edge;
    for (int i = 1; i <= q; ++i) {
        char o;
        std::cin >> o;
        if (o == 'D') {
            int x;
            std::cin >> x, --x;
            Dis[x] = i - 1;
        } else if (o == 'A') {
            int x, y;
            std::cin >> x >> y, --x, --y;
            Edge.emplace_back(std::make_pair(x, y), q);
        } else if (o == 'R') {
            int e;
            std::cin >> e, --e;
            Edge[e].second = i - 1;
        }
    }
    std::vector<std::vector<std::pair<int, int> > > To(n);
    for (auto [e, d] : Edge) {
        auto [u, v] = e;
        To[u].emplace_back(v, d);
        To[v].emplace_back(u, d);
    }
    std::priority_queue<std::pair<int, int> > Que;
    for (int i = 0; i < n; ++i) Que.emplace(Dis[i], i);
    while (!Que.empty()) {
        auto [D, u] = Que.top();
        Que.pop();
        if (D != Dis[u]) continue;
        for (auto [v, d] : To[u]) {
            if (std::min(D, d) > Dis[v]) {
                Dis[v] = std::min(D, d);
                Que.emplace(Dis[v], v);
            }
        }
    }
    for (int D : Dis) std::cout << D << '\n';
    return 0;
}