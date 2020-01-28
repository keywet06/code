#include <bits/stdc++.h>
const int to[2][8] = {
    { -1, -1, -1, 0, 0, 1, 1, 1 },
    { -1, 0, 1, -1, 1, -1, 0, 1 }
};
int ans, q, T, x, y;
std::map<int, std::map<int, int> > map;
std::map<std::pair<int, int>, std::pair<int, int> > f;
std::pair<int, int> find(std::pair<int, int> v);
std::pair<int, int> merge(std::pair<int, int> a, std::pair<int, int> b);
int bomb(std::pair<int, int> a, std::pair<int, int> b);
inline std::pair<int, int> find(std::pair<int, int> v) {
    return f[v] == std::make_pair(0, 0) ? v : f[v] = find(f[v]);
}
inline std::pair<int, int> merge(std::pair<int, int> a, std::pair<int, int> b) {
    return find(a) != find(b) ? f[find(a)] = find(b) : find(a);
}
inline int bomb(std::pair<int, int> a, std::pair<int, int> b) {
    return std::max(std::abs(a.first - b.first), std::abs(a.second - b.second))
      <= 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> q >> T;
    ans = 1;
    for (int i = 1; i <= q; ++i) {
        std::cin >> x >> y;
        if (T && i - 1) {
            x ^= ans;
            y ^= ans;
        }
        std::vector<std::pair<int, int> > vector;
        std::pair<int, int> first;
        for (int j = 0; j < 8; ++j) {
            if (map[x + to[0][j]][y + to[1][j]]) {
                vector.push_back(std::make_pair(x + to[0][j], y + to[1][j]));
            }
        }
        if (!vector.size()) {
            map[x][y] = 1;
            std::cout << ans << std::endl;
            continue;
        }
        int cnt = !bomb(vector[0], vector[vector.size() - 1]);
        std::map<std::pair<int, int>, int> smap;
        if (cnt) {
            ++smap[find(vector[vector.size() - 1])];
        }
        for (int j = 1; j < vector.size(); ++j) {
            if (vector[j] != vector[j - 1]) {
                ++cnt;
                ++smap[find(vector[j - 1])];
            }
        }
        if (map[x - 1][y] && map[x][y - 1] && map[x + 1][y] && map[x][y + 1]) {
            --ans;
        } else {
            for (std::map<std::pair<int, int>, int>::iterator it = smap.begin();
              it != smap.end(); ++it) {
                ans += (*it).second - 1;
                merge(vector[0], (*it).first);
            }
        }
        map[x][y] = 1;
        std::cout << ans << std::endl;
    }
    return 0;
}