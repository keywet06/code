#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;

const int P = 998244353;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? x += P : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Sqr(int x) { return Mul(x, x); }
inline int &Sqrs(int &x) { return Muls(x, x); }

inline int Pow(int Base, int64 Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Sqrs(Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Pow(x, P - 2); }

inline int &Pows(int &Base, int64 Exp) { return Base = Pow(Base, Exp); }
inline int &Invs(int &x) { return Pows(x, P - 2); }

inline int Div(int x, int y) { return Mul(x, Inv(y)); }
inline int &Divs(int &x, int y) { return Muls(x, Inv(y)); }

#define templ template <typename... Args>

templ int Add(int x, int y, Args... args) { return Add(Add(x, y), args...); }
templ int Sub(int x, int y, Args... args) { return Sub(Sub(x, y), args...); }
templ int Mul(int x, int y, Args... args) { return Mul(Mul(x, y), args...); }
templ int Div(int x, Args... args) { return Mul(x, Inv(Mul(args...))); }
templ int &Adds(int &x, int y, Args... args) { return Adds(Adds(x, y), args...); }
templ int &Subs(int &x, int y, Args... args) { return Subs(Subs(x, y), args...); }
templ int &Muls(int &x, int y, Args... args) { return Muls(Muls(x, y), args...); }
templ int &Divs(int &x, Args... args) { return Muls(x, Inv(Mul(args...))); }

#undef templ

inline int PAdd(const int P, int x, int y) { return (x += y) >= P ? x - P : x; }
inline int PSub(const int P, int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int PMul(const int P, int x, int y) { return int64(x) * y % P; }
inline int &PAdds(const int P, int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &PSubs(const int P, int &x, int y) { return (x -= y) < 0 ? x += P : x; }
inline int &PMuls(const int P, int &x, int y) { return x = int64(x) * y % P; }

inline int Read() {
    int x = 0, ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    do {
        x = (x << 3) + (x << 1) + (ch ^ '0');
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return x;
}

const int K = 1e8;
const int N = 1e6;
const int Z = (32 - __builtin_clz(K - 1)) * (N + 1);

int Root = -1;

struct SNode {
    int ls, rs, Num, Sum;
    SNode() {}
    SNode(int L, int R, int N, int S) : ls(L), rs(R), Num(N), Sum(S) {}
};

int SegCnt;

SNode Seg[Z];

inline int Compo(int LSum, int RSum, int RNum, int LLen) { return Add(LSum, RSum, Mul(RNum, LLen + 1)); }
inline int GLNum(int u) { return (u = Seg[u].ls) == -1 ? 0 : Seg[u].Num; }
inline int GLSum(int u) { return (u = Seg[u].ls) == -1 ? 0 : Seg[u].Sum; }
inline int GRNum(int u) { return (u = Seg[u].rs) == -1 ? 0 : Seg[u].Num; }
inline int GRSum(int u) { return (u = Seg[u].rs) == -1 ? 0 : Seg[u].Sum; }

inline void Update(int &u, int l, int r, int x) {
    if (u == -1) Seg[u = SegCnt++] = SNode(-1, -1, 0, 0);
    if (l == r) return ++Seg[u].Num, void(0);
    int Mid = l + r >> 1;
    x <= Mid ? Update(Seg[u].ls, l, Mid, x) : Update(Seg[u].rs, Mid + 1, r, x);
    Seg[u].Num = GLNum(u) + GRNum(u);
    Seg[u].Sum = Compo(GLSum(u), GRSum(u), GRNum(u), Mid - l);
}

int n, k;

inline void Updates(int x) { Update(Root, 0, k - 1, x); };

struct Segu {
    int Len, Num, Sum;
    Segu(int L, int N, int S) : Len(L), Num(N), Sum(S) {}
    Segu Reverse() { return Segu(Len, Num, Sub(Mul(Len, Num), Sum)); }
};

inline Segu CompoS(Segu l, Segu r) { return Segu(l.Len + r.Len + 1, l.Num + r.Num, Compo(l.Sum, r.Sum, r.Num, l.Len)); }

inline Segu Query(int u, int l, int r, int x, int y) {
    if (u == -1) return Segu(std::min(y, r) - std::max(x, l), 0, 0);
    if (l >= x && r <= y) return Segu(r - l, Seg[u].Num, Seg[u].Sum);
    int Mid = l + r >> 1;
    if (y <= Mid) {
        return Query(Seg[u].ls, l, Mid, x, y);
    } else if (x > Mid) {
        return Query(Seg[u].rs, Mid + 1, r, x, y);
    } else {
        return CompoS(Query(Seg[u].ls, l, Mid, x, y), Query(Seg[u].rs, Mid + 1, r, x, y));
    }
}

inline Segu Querys(int x, int y) { return Query(Root, 0, k - 1, x, y); }

int main() {
    n = Read(), k = Read();
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) a[i] = Read();
    for (int i = 1; i <= n; ++i) PAdds(k, a[i], a[i - 1]);
    std::map<int, std::tuple<int, int, int> > Map;
    for (int i = 0; i <= n; ++i) {
        auto &p = Map[a[i]];
        int &Num = std::get<0>(p), &Last = std::get<1>(p), &Id = std::get<2>(p);
        ++Num, Last = -1, Id = 0;
    }
    int Ans = Sub(0, Div(Mul(n, n + 1), 2));
    for (int i = 0; i <= n; ++i) {
        auto &p = Map[a[i]];
        int &Num = std::get<0>(p), &Last = std::get<1>(p), &Id = std::get<2>(p);
        if (!Id) Adds(Ans, Div(Mul(Num, Num - 1), 2));
        if (++Id, Num > 1) {
            int Sum = 0, M = a[i], R = a[i] + k / 2, L = a[i] - (k + 1) / 2 + 1;
            if (R < k) {
                Adds(Sum, Querys(M, R).Sum);
            } else {
                Adds(Sum, CompoS(Querys(M, k - 1), Querys(0, R - k)).Sum);
            }
            if (L >= 0) {
                Adds(Sum, Querys(L, M).Reverse().Sum);
            } else {
                Adds(Sum, CompoS(Querys(L + k, k - 1), Querys(0, M)).Reverse().Sum);
            }
            Adds(Ans, Mul(Sub(Id << 1, Num + 1), Sum));
        }
        Updates(a[i]);
    }
    std::cout << Ans << std::endl;
    return 0;
}