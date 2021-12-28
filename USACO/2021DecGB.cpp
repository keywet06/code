#include <bits/stdc++.h>

const int N = 200005;

int n, x, y, z, ans;
int p[N], q[N], c[N];

std::set<int> S1;

std::vector<int> AddHi[N], DelHi[N], AddLo[N], DelLo[N];

inline void Del(int x) {
    S1.erase(x);
    auto it = S1.lower_bound(x);
    int r = c[*it], m = c[x];
    int l = c[*--it];
    ans -= l == 0 && m == 1;
    ans -= m == 0 && r == 1;
    ans += l == 0 && r == 1;
}

inline void Add(int x, int m) {
    c[x] = m;
    auto it = S1.lower_bound(x);
    int r = c[*it];
    int l = c[*--it];
    ans -= l == 0 && r == 1;
    ans += l == 0 && m == 1;
    ans += m == 0 && r == 1;
    S1.insert(x);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> p[i], q[p[i]] = i;
    S1.insert({0, n + 1});
    for (int i = 1; i <= n; ++i) {
        DelHi[i].push_back(q[i]);
        AddLo[i].push_back(q[i]);
        auto it = S1.lower_bound(p[i]);
        DelLo[*it].push_back(i);
        AddHi[*--it].push_back(i);
        S1.insert(p[i]);
    }
    S1.clear();
    S1.insert({0, n + 1}), c[0] = 1;
    for (int i = 0; i <= n; ++i) {
        for (int x : DelHi[i]) Del(x);
        for (int x : DelLo[i]) Del(x);
        for (int x : AddHi[i]) Add(x, 0);
        for (int x : AddLo[i]) Add(x, 1);
        std::cout << ans << '\n';
    }
    return 0;
}