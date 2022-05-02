#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

using int32 = int;
using int64 = long long;

inline int BiClz(int32 x) { return __builtin_clz(x); }

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    int N = BiBlm(n + 1) << 1;
    std::vector<int> Seg(N), Tag(N), Sum(N), Min(N);
    auto PushDownT = [&](int u) -> void {
        if (!Tag[u]) return;
        Seg[u << 1] = Mul(Sum[u << 1], Tag[u << 1] = Tag[u]);
        Seg[u << 1 | 1] = Mul(Sum[u << 1 | 1], Tag[u << 1 | 1] = Tag[u]);
        Tag[u] = 0;
    };
    std::function<void(int, int, int, int, int, int)> Update = [&](int u, int l, int r, int x, int y, int v) -> void {
        if (l >= x && r <= y) return void(Seg[u] = Mul(Sum[u], Tag[u] = v));
        int Mid = l + r >> 1;
        PushDownT(u);
        if (x <= Mid) Update(u << 1, l, Mid, x, y, v);
        if (y > Mid) Update(u << 1 | 1, Mid + 1, r, x, y, v);
        Seg[u] = Add(Seg[u << 1], Seg[u << 1 | 1]);
    };
    auto Updates = [&](int x, int y, int v) -> void { Update(1, 0, n, x, y, v); };
    std::function<void(int, int, int, int, int)> Modify = [&](int u, int l, int r, int x, int v) -> void {
        if (l == r) return void(Seg[u] = Mul(Tag[u], Sum[u] = v));
        PushDownT(u);
        int Mid = l + r >> 1;
        x <= Mid ? Modify(u << 1, l, Mid, x, v) : Modify(u << 1 | 1, Mid + 1, r, x, v);
        Seg[u] = Add(Seg[u << 1], Seg[u << 1 | 1]);
        Sum[u] = Add(Sum[u << 1], Sum[u << 1 | 1]);
    };
    auto Modifys = [&](int x, int v) -> void { Modify(1, 0, n, x, v); };
    std::function<void(int, int, int, int, int)> Let = [&](int u, int l, int r, int x, int v) -> void {
        if (l == r) return void(Min[u] = v);
        int Mid = l + r >> 1;
        x <= Mid ? Let(u << 1, l, Mid, x, v) : Let(u << 1 | 1, Mid + 1, r, x, v);
        Min[u] = std::min(Min[u << 1], Min[u << 1 | 1]);
    };
    std::vector<int> Last(n + 1);
    auto Lets = [&](int x, int v) -> void { Last[x] = v, Let(1, 0, n, x, v); };
    std::function<int(int, int, int, int, int)> LMin = [&](int u, int l, int r, int x, int y) -> int {
        if (l >= x && r <= y) return Min[u];
        int Mid = l + r >> 1;
        if (y <= Mid) {
            return LMin(u << 1, l, Mid, x, y);
        } else if (x > Mid) {
            return LMin(u << 1 | 1, Mid + 1, r, x, y);
        }
        return std::min(LMin(u << 1, l, Mid, x, y), LMin(u << 1 | 1, Mid + 1, r, x, y));
    };
    auto LMins = [&](int x, int y) -> int { return LMin(1, 0, n, x, y); };
    Modifys(0, 1);
    int Ans, Cnt = 0;
    for (int x, i = 1; i <= n; ++i) {
        std::cin >> x;
        int L = Last[x], R = x ? LMins(0, x - 1) - 1 : i - 1, j = x;
        while (L <= R) Updates(L, R, j + 1), Mid(R, Last[++j] - 1);
        Lets(x, i), Modifys(i, Ans = Seg[1]);
    }
    std::cout << Ans << std::endl;
    return 0;
}
