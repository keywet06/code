#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

#define templ template <typename Type1, typename Type2>
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return x > y ? x : x = y; }
#undef templ

using int64 = long long;

const int N = 500005;

int n, m;
int Dep[N], MDep[N], Son[N], Size[N], rx[N], ry[N], rz[N];

int64 Ans[N];

std::vector<int> To[N];

inline void Dfs1(int u, int f) {
    MDep[u] = Dep[u] = Dep[f] + 1, Size[u] = 1;
    for (auto v : To[u]) {
        if (v == f) continue;
        Dfs1(v, u), Mad(MDep[u], MDep[v]), Size[u] += Size[v];
        if (MDep[v] > MDep[Son[u]]) Son[u] = v;
    }
}

inline void Dfs2(int u, int f, int UpS, std::vector<int64> &Sum, std::vector<int> &Num) {
    if (Son[u]) Dfs2(Son[u], u, UpS, Sum, Num);
    for (auto v : To[u]) {
        if (v == f || v == Son[u]) continue;
        std::vector<int64> Sv(MDep[v] - Dep[v] + 2);
        std::vector<int> Nv(MDep[v] - Dep[v] + 2);
        Dfs2(v, u, Dep[v], Sv, Nv);
        for (int i = Dep[v]; i <= MDep[v]; ++i) {
            Sum[i - UpS] += Sv[i - Dep[v]];
            Num[i - UpS] += Nv[i - Dep[v]];
        }
    }
    Debug << "Node#" << u << ": " << std::endl;
    Debug << "Num(" << UpS << ") = ";
    for (auto x : Num) Deb << x << ' ';
    Deb << std::endl;
    Debug << "Sum(" << UpS << ") = ";
    for (auto x : Sum) Deb << x << ' ';
    Deb << std::endl;
    Deb << "AllSum = " << Sum[Dep[u] - UpS + 1] << ", AllNum = " << Num[Dep[u] - UpS + 1] << std::endl;
    int64 AllSum = Sum[Dep[u] - UpS + 1], AllNum = Num[Dep[u] - UpS + 1];
    auto Addu = [&]() { Sum[Dep[u] - UpS] = AllSum + Dep[u], Num[Dep[u] - UpS] = AllNum + 1; };
    int x = rx[u], y = ry[u], z = rz[u];
    int l = std::max(x, m - int(AllSum)), r = std::min(Dep[u] - 1, m - y), d;
    if (l > r || Dep[u] - 1 < x || AllSum < y || Dep[u] + Size[u] - 2 < m || x + y > m) return Ans[u] = -1, Addu();
    auto GetD = [&](int d) {
        int k = m - d;
        int64 l1 = d * (d + 1LL) / 2 + z, r1 = (Dep[u] - 1LL) * Dep[u] / 2 - (Dep[u] - 1LL - d) * (Dep[u] - d) / 2 + z;
        int L = Dep[u] + 1 - UpS, R = MDep[u] - UpS, D;
        Debug << "[[" << L << ", " << R << "]]" << std::endl;
        while (L < R) D = L + R >> 1, AllNum - Num[D + 1] >= k ? R = D : L = D + 1;
        Debug << "[[" << L << "]]" << std::endl;
        int64 l2 = AllSum - Sum[L + 1] - (L + UpS) * (AllNum - Num[L + 1] - k) - k * int64(Dep[u]);
        L = Dep[u] + 1 - UpS, R = MDep[u] - UpS;
        while (L < R) D = L + R + 1 >> 1, Num[D] >= k ? L = D : R = D - 1;
        int64 r2 = Sum[L] - int64(L + UpS) * (Num[L] - k) - k * int64(Dep[u]);
        Debug << "[[" << L << "]]" << std::endl;
        Debug << "S1#" << d << ": [" << l1 << ", " << r1 << "] & [" << l2 << ", " << r2 << "]" << std::endl;
        return std::make_tuple(l1, l2, r1, r2);
    };
    while (l + 1 < r) {
        auto [l1, l2, r1, r2] = GetD(d = l + r >> 1);
        if (r2 < l1) {
            r = d;
        } else if (r1 < l2) {
            l = d;
        } else {
            return Ans[u] = 0, Addu();
        }
    }
    Ans[u] = INT64_MAX;
    for (int d = l; d <= r; ++d) {
        auto [l1, l2, r1, r2] = GetD(d);
        Mid(Ans[u], r2 < l1 ? l1 - r2 : r1 < l2 ? l2 - r1 : 0);
    }
    Addu();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1, x, y; i < n; ++i) {
        std::cin >> x >> y;
        To[x].push_back(y);
        To[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) std::cin >> rx[i] >> ry[i] >> rz[i];
    Dfs1(1, 1);
    std::vector<int64> S1(MDep[1] + 1);
    std::vector<int> N1(MDep[1] + 1);
    Dfs2(1, 1, 1, S1, N1);
    for (int i = 1; i <= n; ++i) std::cout << Ans[i] << " \n"[i == n];
    return 0;
}