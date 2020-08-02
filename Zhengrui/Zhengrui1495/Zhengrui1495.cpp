#include <bits/stdc++.h>
const int N = 100005;
int ans, n, m, x, y, min;
int a[N], l1[N], l2[N], c[N];
std::vector<int> to[N];
std::set<int> set;
int main() {
    srand(time(NULL));
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> l1[i] >> l2[i];
        to[l1[i]].push_back(l2[i]);
        to[l2[i]].push_back(l1[i]);
    }
    for (int i = 1; i <= n; ++i) a[i] = rand() % 3;
    for (int i = 1; i <= m; ++i) ans += a[l1[i]] == a[l2[i]];
    while (ans) {
        for (int i = 1; i <= n; ++i) {
            c[0] = c[1] = c[2] = 0;
            for (int j = 0; j < to[i].size(); ++j) ++c[a[to[i][j]]];
            x = std::min(c[0], std::min(c[1], c[2]));
            set.clear();
            if (c[0] == x) set.insert(0);
            if (c[1] == x) set.insert(1);
            if (c[2] == x) set.insert(2);
            ans -= c[a[i]];
            x = rand() % set.size();
            std::set<int>::iterator it = set.begin();
            for (int j = 0; j < x; ++j) ++it;
            ans += c[a[i] = *it];
        }
    }
    for (int i = 1; i <= n; ++i) std::cout << a[i] + 1 << ' ';
    std::cout << std::endl;
    return 0;
}