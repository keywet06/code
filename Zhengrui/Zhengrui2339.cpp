#include <bits/stdc++.h>

#define templ template <typename Type1, typename Type2>
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return x > y ? x : x = y; }
#undef templ

using int64 = long long;

const int N = 5005;

int n, k;
int a[N], sl[N], sr[N], sw[N], p[N];

int64 f[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> sl[i] >> sr[i] >> sw[i];
        a[i] = sl[i], a[i + n] = sr[i];
    }
    int m = n << 1;
    std::sort(a + 1, a + m + 1);
    m = std::unique(a + 1, a + m + 1) - a - 1;
    int64 as = 0;
    for (int i = 1; i <= n; ++i) {
        p[i] = i, as += sw[i];
        sl[i] = std::lower_bound(a + 1, a + m + 1, sl[i]) - a;
        sr[i] = std::lower_bound(a + 1, a + m + 1, sr[i]) - a;
    }
    std::sort(p + 1, p + n + 1, [](int x, int y) { return sr[x] < sr[y]; });
    for (int i = 0; i < m; ++i) {
        Mad(f[i + 1], f[i]);
        int64 s = 0;
        std::priority_queue<int> Que;
        for (int j = 1; j <= n; ++j) {
            if (sl[p[j]] > i) s += sw[p[j]], Que.push(-sw[p[j]]);
            if (Que.size() > k) s += Que.top(), Que.pop();
            if (s) Mad(f[sr[p[j]]], f[i] + s);
        }
    }
    std::cout << as - f[m] << '\n';
    return 0;
}