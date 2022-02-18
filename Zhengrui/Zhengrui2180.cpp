#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

using int32 = int;
using int64 = long long;

inline int BiClz(int32 x) { return __builtin_clz(x); }

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n, m, q;
    std::cin >> n >> m >> q;
    int xl, yl, xr, yr, w;
    struct Node {
        int ls, rs;
        int64 plus, max;
        Node() : ls(-1), rs(-1), plus(0), max(0) {}
    };
    int R = -1;
    std::vector<Node *> Tr;
    auto GMax = [&](int u) { return u == -1 ? 0 : Tr[u]->max; };
    using AddType = std::function<void(int &, int, int, int, int)>;
    AddType Add = [&](int &u, int lx, int rx, int ly, int ry) {
        if (u == -1) u = Tr.size(), Tr.push_back(new Node());
        if (lx >= xl && rx <= xr && ly >= yl && ry <= yr) {
            return void((Tr[u]->plus += w, Tr[u]->max += w));
        }
        if (rx - lx >= ry - ly) {
            int Mid = lx + rx >> 1;
            if (xl <= Mid) Add(Tr[u]->ls, lx, Mid, ly, ry);
            if (xr > Mid) Add(Tr[u]->rs, Mid + 1, rx, ly, ry);
        } else {
            int Mid = ly + ry >> 1;
            if (yl <= Mid) Add(Tr[u]->ls, lx, rx, ly, Mid);
            if (yr > Mid) Add(Tr[u]->rs, lx, rx, Mid + 1, ry);
        }
        Tr[u]->max = std::max(GMax(Tr[u]->ls), GMax(Tr[u]->rs)) + Tr[u]->plus;
    };
    while (m--) std::cin >> xl >> yl >> xr >> yr >> w, Add(R, 1, n, 1, n);
    using FindType = std::function<int64(int, int, int, int, int)>;
    FindType Find = [&](int u, int lx, int rx, int ly, int ry) {
        if (u == -1) return 0ll;
        if (lx >= xl && rx <= xr && ly >= yl && ry <= yr) return Tr[u]->max;
        int64 Ret = 0;
        if (rx - lx >= ry - ly) {
            int Mid = lx + rx >> 1;
            if (xl <= Mid) Mad(Ret, Find(Tr[u]->ls, lx, Mid, ly, ry));
            if (xr > Mid) Mad(Ret, Find(Tr[u]->rs, Mid + 1, rx, ly, ry));
        } else {
            int Mid = ly + ry >> 1;
            if (yl <= Mid) Mad(Ret, Find(Tr[u]->ls, lx, rx, ly, Mid));
            if (yr > Mid) Mad(Ret, Find(Tr[u]->rs, lx, rx, Mid + 1, ry));
        }
        return Ret + Tr[u]->plus;
    };
    while (q--) {
        std::cin >> xl >> yl >> xr >> yr;
        std::cout << Find(R, 1, n, 1, n) << std::endl;
    }
    return 0;
}