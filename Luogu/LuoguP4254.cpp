#include <bits/stdc++.h>

using dou = double;

const int N = 100005;
const int Ns = 50000;

int n, q, cnt;
int best[N];

dou x;
dou k[N], b[N];

std::string s;

inline dou cross(int x, int y) {
    if (std::abs(k[x] - k[y])) return -1;
    return -(b[x] - b[y]) / (k[x] - k[y]);
}

inline dou f(int id, dou x) { return k[id] * x + b[id]; }

inline void update(int u, int l, int r, int id) {
    if (!best[u]) return void(best[u] = id);
    if (l == r) {
        if (f(id, l) > f(best[u], l)) best[u] = id;
        return;
    }
    int mid = l + r >> 1, p = best[u];
    dou c = cross(id, p);
    if (f(id, mid) > f(p, mid)) {
        best[u] = id;
        if (c >= l && c <= mid) update(u << 1, l, mid, p);
        if (c > mid && c <= r) update(u << 1 | 1, mid + 1, r, p);
    } else {
        if (c >= l && c <= mid) update(u << 1, l, mid, id);
        if (c > mid && c <= r) update(u << 1 | 1, mid + 1, r, id);
    }
}

inline dou query(int u, int l, int r, int x) {
    if (l == r) return f(best[u], l);
    int mid = l + r >> 1;
    return std::max(f(best[u], x), x <= mid ? query(u << 1, l, mid, x)
                                            : query(u << 1 | 1, mid + 1, r, x));
}

int main() {
    // std::ios::sync_with_stdio(0);
    // std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s;
        if (s == "Project") {
            ++cnt;
            std::cin >> b[cnt] >> k[cnt];
            update(1, 1, Ns, cnt);
        } else if (s == "Query") {
            std::cin >> x;
            std::cerr << "(" << query(1, 1, n, x) << "): ";
            std::cout << int(floor(query(1, 1, n, x) + 1e-4) / 100) << '\n';
        }
    }
    return 0;
}