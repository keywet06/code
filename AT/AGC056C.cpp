#include <bits/stdc++.h>

const int N = 1000005;

int n, m, x, y;
int dis[N];

std::vector<int> toa[N], tob[N];

std::deque<int> q;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y, --x;
        tob[x].push_back(y);
        tob[y].push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        toa[i].push_back(i + 1);
        toa[i + 1].push_back(i);
    }
    dis[0] = 1, q.push_back(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (int v : toa[u]) {
            if (dis[v]) continue;
            dis[v] = dis[u] + 1;
            q.push_back(v);
        }
        for (int v : tob[u]) {
            if (dis[v]) continue;
            dis[v] = dis[u];
            q.push_front(v);
        }
    }
    for (int i = 0; i < n; ++i) std::cout << (dis[i] > dis[i + 1]);
    std::cout << '\n';
    return 0;
}