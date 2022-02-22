#include <bits/stdc++.h>

using int64 = long long;

const int P = 1000000007;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? x += P : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Sqr(int x) { return Mul(x, x); }
inline int &Sqrs(int &x) { return Muls(x, x); }

inline int Pow(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Sqrs(Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Pow(x, P - 2); }

inline int Div(int x, int y) { return Mul(x, Inv(y)); }
inline int &Divs(int &x, int y) { return Muls(x, Inv(y)); }

template <typename... Args>
inline int Add(int x, int y, Args... args) {
    return Add(Add(x, y), args...);
}

template <typename... Args>
inline int Sub(int x, int y, Args... args) {
    return Sub(Sub(x, y), args...);
}

template <typename... Args>
inline int Mul(int x, int y, Args... args) {
    return Mul(Mul(x, y), args...);
}

template <typename... Args>
inline int Div(int x, Args... args) {
    return Mul(x, Inv(Mul(args...)));
}

template <typename... Args>
inline int &Adds(int &x, int y, Args... args) {
    return Adds(Adds(x, y), args...);
}

template <typename... Args>
inline int &Subs(int &x, int y, Args... args) {
    return Subs(Subs(x, y), args...);
}

template <typename... Args>
inline int &Muls(int &x, int y, Args... args) {
    return Muls(Muls(x, y), args...);
}

template <typename... Args>
inline int &Divs(int &x, Args... args) {
    return Muls(x, Inv(Mul(args...)));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<int> > To(n);
    for (int i = 1, x, y; i < n; ++i) {
        std::cin >> x >> y, --x, --y;
        To[x].push_back(y);
        To[y].push_back(x);
    }
    struct Solver {
        int ASum, ASqr;
        Solver() : ASum(0), ASqr(0) {}
    };
    std::vector<Solver> Sol(n);
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        int PSum = 0, Sum = 0, SSqr = 0;
        for (int j = 0, p, x; j < m; ++j) {
            std::cin >> p >> x;
            Adds(PSum, p), Adds(Sum, Mul(p, x)), Adds(SSqr, Mul(p, Sqr(x)));
        }
        Sol[i].ASum = Div(Sum, PSum), Sol[i].ASqr = Div(SSqr, PSum);
    }
    auto Link = [&](Solver &A, Solver &B) -> Solver & {
        Adds(A.ASqr, B.ASqr, Mul(2, A.ASum, B.ASum));
        Adds(A.ASum, B.ASum);
        return A;
    };
    std::vector<int> Ans(n);
    std::function<void(int, int)> Dfs = [&](int u, int Fa) -> void {
        for (int v : To[u]) {
            if (v != Fa) Dfs(v, u), Link(Sol[u], Sol[v]);
        }
        Ans[u] = Sub(Sol[u].ASqr, Sqr(Sol[u].ASum));
    };
    Dfs(0, -1);
    for (int i = 0; i < n; ++i) std::cout << Ans[i] << '\n';
    return 0;
}
