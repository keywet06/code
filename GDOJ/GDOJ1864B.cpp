#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;
const int T = N << 1;
const int M = N << 2;

int n, m;
int s[T], Cur[T], Pre[T], a[N], b[N], o[N], Deg[M], Te[M], Si[M];

std::vector<std::pair<int, int> > To[T];

inline void Insert(int x, int y, int Id) {
    To[x].emplace_back(y, Id);
    To[y].emplace_back(x, Id);
}

inline void Dfs(int u) {
    for (int &e = Cur[u]; e < To[u].size(); ++e) {
        int v = To[u][e].first, Id = To[u][e].second;
        if (!Te[Id]) Te[Id] = 1, Si[Id] = u, Dfs(v);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i], s[i] = a[i];
    for (int i = 0; i < n; ++i) std::cin >> b[i], s[n + i] = b[i];
    for (int i = 0; i < n; ++i) {
        if (a[i] > b[i]) std::swap(a[i], b[i]), o[i] ^= 1;
    }
    std::sort(s, s + n + n);
    int m = std::unique(s, s + n + n) - s;
    for (int i = 0; i < n; ++i) {
        ++Deg[a[i] = std::lower_bound(s, s + m, a[i]) - s];
        ++Deg[b[i] = std::lower_bound(s, s + m, b[i]) - s];
        Insert(a[i], b[i], i);
    }
    for (int i = 0, l = -1; i < m; ++i) {
        if ((Deg[i] & 1) == 0) continue;
        if (l > -1) {
            Insert(i, l, n + i), l = -1;
        } else {
            l = i;
        }
    }
    for (int i = 0; i < m; ++i) {
        if (Cur[i] != To[i].size()) Dfs(i);
    }
    for (int i = 0; i < n; ++i) {
        if (Si[i] == b[i]) std::swap(a[i], b[i]), o[i] ^= 1;
    }
    int64 Ans = 0;
    for (int i = 0; i < n; ++i) ++Pre[a[i]];
    for (int i = m - 1; i; --i) Pre[i - 1] += Pre[i];
    for (int i = 0; i < n; ++i) Ans += int64(s[b[i]]) * Pre[b[i] + 1];
    memset(Pre, 0, sizeof(Pre));
    for (int i = 0; i < n; ++i) ++Pre[b[i]];
    for (int i = m - 1; i; --i) Pre[i - 1] += Pre[i];
    for (int i = 0; i < n; ++i) Ans += int64(s[a[i]]) * Pre[a[i]];
    std::cout << Ans << '\n';
    for (int i = 0; i < n; ++i) std::cout << o[i] << " \n"[i == n - 1];
    return 0;
}