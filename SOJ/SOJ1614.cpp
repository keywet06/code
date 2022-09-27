#include <bits/stdc++.h>

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename Type, Type P, typename MulType = Type>
class ModInt {
   protected:
    Type x;

   public:
    using Self = ModInt<Type, P, MulType>;
    ModInt() : x(0) {}
    ModInt(Type c) : x(c) {}
    explicit operator Type() { return x; }
    Type &Data() { return x; }
    friend Self operator+(Self a, Self b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend Self operator-(Self a, Self b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend Self operator*(Self a, Self b) { return MulType(a.x) * b.x % P; }
    friend Self &operator+=(Self &a, Self b) { return (a.x += b.x) >= P ? a.x -= P, a : a; }
    friend Self &operator-=(Self &a, Self b) { return (a.x -= b.x) < 0 ? a.x += P, a : a; }
    friend Self &operator*=(Self &a, Self b) { return a.x = MulType(a.x) * b.x % P, a; }
#define templ template <typename ExpType>
    templ Self Pow(ExpType Exp) {
        Self Base(*this), Ret(1);
        while (Exp) {
            if (Exp & 1) Ret *= Base;
            Base *= Base, Exp >>= 1;
        }
        return Ret;
    }
    templ Self &Pows(ExpType Exp) { return *this = Pow(Exp); }
    templ Self &PowEq(ExpType Exp) { return Pows(Exp); }
    templ Self &PowEqual(ExpType Exp) { return Pows(Exp); }
    templ friend Self Pow(Self Base, ExpType Exp) { return Base.Pow(Exp); }
#undef templ
    Self Inv() { return Pow(P - 2); }
    Self &Invs() { return Pows(P - 2); }
    Self &InvEq() { return Invs(); }
    Self &InvEqual() { return Invs(); }
    friend Self Inv(Self x) { return x.Pow(P - 2); }
    friend Self operator~(Self x) { return x.Inv(); }
    friend Self operator/(Self a, Self b) { return a * ~b; }
    friend Self &operator/=(Self &a, Self b) { return a *= ~b; }
    friend Self &operator++(Self &a) { return a += 1; }
    friend Self &operator--(Self &a) { return a -= 1; }
    friend Self operator++(Self &a, int) {
        Self Tmp = a;
        return a += 1, Tmp;
    }
    friend Self operator--(Self &a, int) {
        Self Tmp = a;
        return a -= 1, Tmp;
    }
    friend Self operator+(Self a) { return a; }
    friend Self operator-(Self a) { return 0 - a; }
    bool operator==(Self a) { return x == int(a); }
};

}  // namespace Oct

#endif

using int64 = long long;

const int P = 998244353;

using MInt = Oct::ModInt<int, P, int64>;

const int N = 500005;
const int M = 1 << 20;

MInt t, A, B;

struct Node {
    MInt lp, rp, tx, Ans;
    Node() : lp(0), rp(0), tx(0), Ans(0) {}
    Node(MInt p) : lp(p), rp(p), tx(p + (1 - p) * t), Ans(A * p) {}
    Node(MInt clp, MInt crp, MInt ctx, MInt cAns) : lp(clp), rp(crp), tx(ctx), Ans(cAns) {}
};

inline Node operator+(Node a, Node b) {
    return Node(a.lp + b.lp * a.tx, a.rp * b.tx + b.rp, a.tx * b.tx, a.Ans + b.Ans + a.rp * b.lp * B);
}

MInt a[N];

Node tr[M];

inline const Node Build(int u, int l, int r) {
    if (l == r) return tr[u] = a[l];
    int Mid = l + r >> 1;
    return tr[u] = Build(u << 1, l, Mid) + Build(u << 1 | 1, Mid + 1, r);
}

inline void Update(int u, int l, int r, int x) {
    if (l == r) return void(tr[u] = a[l]);
    int Mid = l + r >> 1;
    x <= Mid ? Update(u << 1, l, Mid, x) : Update(u << 1 | 1, Mid + 1, r, x);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
}

inline Node Query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return tr[u];
    int Mid = l + r >> 1;
    if (y <= Mid) return Query(u << 1, l, Mid, x, y);
    if (x > Mid) return Query(u << 1 | 1, Mid + 1, r, x, y);
    return Query(u << 1, l, Mid, x, y) + Query(u << 1 | 1, Mid + 1, r, x, y);
}

int n, q, x, y;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> x >> n >> q >> x >> y, t = MInt(x) / y, std::cin >> x >> y, A = x, A += B = y;
    for (int i = 1; i <= n; ++i) std::cin >> x >> y, a[i] = MInt(x) / y;
    Build(1, 1, n);
    for (int i = 1, o, e; i <= q; ++i) {
        std::cin >> o;
        if (o == 0) {
            std::cin >> e >> x >> y, a[e] = MInt(x) / y;
            Update(1, 1, n, e);
        } else {
            std::cin >> x >> y;
            std::cout << int(Query(1, 1, n, x, y).Ans) << '\n';
        }
    }
    return 0;
}