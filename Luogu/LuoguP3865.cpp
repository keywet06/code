#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;

inline int BiFfs(int32 x) { return __builtin_ffs(x); }
inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }
inline int BiPop(int32 x) { return __builtin_popcount(x); }
inline int BiPar(int32 x) { return __builtin_parity(x); }
inline int BiFfs(int64 x) { return __builtin_ffsll(x); }
inline int BiClz(int64 x) { return __builtin_clzll(x); }
inline int BiCtz(int64 x) { return __builtin_ctzll(x); }
inline int BiPop(int64 x) { return __builtin_popcountll(x); }
inline int BiPar(int64 x) { return __builtin_parityll(x); }

template <typename Type, typename Oper>
class ST {
   protected:
    std::vector<std::vector<Type> > St;

   public:
    ST(std::vector<Type> a) {
        int n = a.size(), m = 31 - BiClz(n);
        St.resize(m + 1), St[0] = a;
        for (int I = 0, i = 1, c = 1; i <= m; ++I, ++i, c <<= 1) {
            int T = n - (c << 1);
            St[i].resize(T);
            for (int j = 0; j < T; ++j) St[i][j] = Oper()(St[I][j], St[I][j + c]);
        }
    }

    inline Type Query(int l, int r) {
        int x = 31 - BiClz(r - l + 1);
        return Oper()(St[x][l], St[x][r - (1 << x) + 1]);
    }
};

class Max {
   public:
    Max() {}
    int operator()(int x, int y) { return std::max(x, y); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    ST<int, Max> St(a);
    int l, r;
    while (q--) std::cin >> l >> r, std::cout << St.Query(--l, --r) << '\n';
    return 0;
}