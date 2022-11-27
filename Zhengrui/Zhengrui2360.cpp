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
    bool operator==(Self a) { return x == Type(a); }
    bool operator!=(Self a) { return x != Type(a); }
};

}  // namespace Oct

#endif

const int T = 170;
const int M = 1000005;
const int B = 340;
const int O = 30000000;
const int N = 100005;
const int P = 1019260817;

using MInt = Oct::ModInt<int, 1019260817, long long>;

int n, q, t, Temp, Cnt;
int a[M], Pri[M], Root[M], lSon[O], rSon[O], Sal[O], z[4];
int b[T][N], c[T][B];

MInt Ans;
MInt Seg[M], w[M], s[O], Inn[M];

std::vector<int> Vec[M];

std::set<int> S[M];
std::set<int>::iterator It;

inline void Modify(int u, int Pos, int V) {
    for (int i = Pos; i / B == Pos / B && i < N; ++i) b[u][i] += V;
    for (int i = Pos / B + 1; i <= n / B; ++i) c[u][i] += V;
}

inline int Query(int u, int Pos) { return b[u][Pos] + c[u][Pos / B]; }

void Modify1(int u, int Pos, int V, int l = 1, int r = n) {
    if (l == r) return void(Seg[u] = V);
    int Mid = l + r >> 1;
    Pos <= Mid ? Modify1(u << 1, Pos, V, l, Mid) : Modify1(u << 1 | 1, Pos, V, Mid + 1, r);
    Seg[u] = Seg[u << 1] * Seg[u << 1 | 1];
}

MInt QuerySeg(int u, int L, int R, int l = 1, int r = n) {
    if (L <= l && r <= R) return Seg[u];
    int Mid = l + r >> 1;
    MInt Res = 1;
    if (L <= Mid) Res *= QuerySeg(u << 1, L, R, l, Mid);
    if (Mid < R) Res *= QuerySeg(u << 1 | 1, L, R, Mid + 1, r);
    return Res;
}

void InsertIt(int &u, int Pos, MInt V, int l = 1, int r = n) {
    if (!u) s[u = Sal[Temp--]] = 1;
    s[u] = s[u] * V;
    if (l == r) return;
    int Mid = l + r >> 1;
    Pos <= Mid ? InsertIt(lSon[u], Pos, V, l, Mid) : InsertIt(rSon[u], Pos, V, Mid + 1, r);
}

void DeleteIt(int &u, int Pos, MInt V, int l = 1, int r = n) {
    s[u] = s[u] * V;
    if (l == r) {
        if (!lSon[u] && !rSon[u] && s[u] == 1) Sal[++Temp] = u, u = 0;
        return;
    }
    int Mid = l + r >> 1;
    Pos <= Mid ? DeleteIt(lSon[u], Pos, V, l, Mid) : DeleteIt(rSon[u], Pos, V, Mid + 1, r);
    if (!lSon[u] && !rSon[u] && s[u] == 1) Sal[++Temp] = u, u = 0;
}

void Modify2(int u, int px, int py, MInt V, bool typ, int l = 1, int r = n) {
    typ ? DeleteIt(Root[u], py, V) : InsertIt(Root[u], py, V);
    if (l == r) return;
    int Mid = l + r >> 1;
    px <= Mid ? Modify2(u << 1, px, py, V, typ, l, Mid) : Modify2(u << 1 | 1, px, py, V, typ, Mid + 1, r);
}

void QueryIt(int u, int Pos, int l = 1, int r = n) {
    if (!u) return;
    if (r <= Pos) return void(Ans *= s[u]);
    int Mid = l + r >> 1;
    QueryIt(lSon[u], Pos, l, Mid);
    if (Pos > Mid) QueryIt(rSon[u], Pos, Mid + 1, r);
}

void QuerySal(int u, int px, int py, int l = 1, int r = n) {
    if (px <= l) return void(QueryIt(Root[u], py));
    int Mid = l + r >> 1;
    QuerySal(u << 1 | 1, px, py, Mid + 1, r);
    if (px <= Mid) QuerySal(u << 1, px, py, l, Mid);
}

inline void CollectIt(int v, int V) {
    z[0] = z[1] = z[2] = z[3] = -1;
    if ((It = S[v].upper_bound(V)) != S[v].end()) z[2] = *It, S[v].erase(It);
    if ((It = S[v].upper_bound(V)) != S[v].end()) z[3] = *It, S[v].erase(It);
    if ((It = S[v].lower_bound(V)) != S[v].begin()) z[1] = *--It, S[v].erase(It);
    if ((It = S[v].lower_bound(V)) != S[v].begin()) z[0] = *--It, S[v].erase(It);
    for (int i = 0; i < 4; ++i)
        if (z[i] >= 0) S[v].insert(z[i]);
}

inline void Insert(int v, int V) {
    CollectIt(v, V);
    if (z[0] >= 0 && z[2] >= 0) Modify2(1, z[0], z[2], Inn[v], 1);
    if (z[1] >= 0 && z[3] >= 0) Modify2(1, z[1], z[3], Inn[v], 1);
    if (z[0] >= 0) Modify2(1, z[0], V, w[v], 0);
    if (z[3] >= 0) Modify2(1, V, z[3], w[v], 0);
    if (z[1] >= 0 && z[2] >= 0) Modify2(1, z[1], z[2], w[v], 0);
    S[v].insert(V);
}

inline void Delete(int v, int V) {
    S[v].erase(V), CollectIt(v, V);
    if (z[0] >= 0 && z[2] >= 0) Modify2(1, z[0], z[2], w[v], 0);
    if (z[1] >= 0 && z[3] >= 0) Modify2(1, z[1], z[3], w[v], 0);
    if (z[0] >= 0) Modify2(1, z[0], V, Inn[v], 1);
    if (z[3] >= 0) Modify2(1, V, z[3], Inn[v], 1);
    if (z[1] >= 0 && z[2] >= 0) Modify2(1, z[1], z[2], Inn[v], 1);
}

inline void Update(int Pos, int V, int coef) {
    for (int i = Vec[V].size(), p, j, v; i--;) {
        if (Pri[p = Vec[V][i]] <= 1000) {
            for (j = 0, v = V; v % Pri[p] == 0; v /= Pri[p]) ++j;
            Modify(p, Pos, j * coef);
        } else if (coef > 0) {
            Insert(p, Pos);
        } else {
            Delete(p, Pos);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> q >> t;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], Modify1(1, i, a[i]);
    for (int i = 2; i < M; ++i) {
        if (Vec[i].empty()) {
            for (int j = Pri[++Cnt] = i; j < M; j += i) Vec[j].push_back(Cnt);
        }
    }
    for (int i = 1; i <= Cnt; ++i) Inn[i] = ~(w[i] = MInt(Pri[i] + 1).Pow(1919810) / MInt(Pri[i]).Pow(114514));
    for (int i = 1; i < O; ++i) Sal[++Temp] = i;
    for (int i = 1; i <= n; ++i) Update(i, a[i], 1);
    for (int op, x, y; q--;) {
        std::cin >> op >> x >> y;
        x ^= t * int(Ans), y ^= t * int(Ans);
        if (op == 1) {
            Update(x, a[x], -1), Update(x, a[x] = y, 1), Modify1(1, x, y);
        } else {
            Ans = Pow(QuerySeg(1, x, y), 114514);
            for (int i = 1; Pri[i] <= 1000; ++i) Ans *= w[i].Pow(std::max(Query(i, y) - Query(i, x - 1) - 2, 0));
            QuerySal(1, x, y);
            std::cout << int(Ans) << '\n';
        }
    }
    return 0;
}