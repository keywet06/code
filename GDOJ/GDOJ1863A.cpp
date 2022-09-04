#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

const int64 INF64 = INT64_MAX >> 3;

const int N = 300005;

struct Heap {
    int n;
    int64 a[N];
    inline int size() { return n; }
    inline void insert(int64 x) {
        int u = ++n;
        a[u] = x;
        while (u > 1 && x < a[u >> 1]) std::swap(a[u], a[u >> 1]), u >>= 1;
    }
    inline int64 top() { return a[1]; }
    inline int64 rank(int i) { return i <= n ? a[i] : INT_MAX; }
    inline void pop() {
        std::swap(a[1], a[n]), a[n--] = 0;
        int u = 1, c;
        while (rank(u << 1) < a[u] || rank(u << 1 | 1) < a[u]) {
            std::swap(a[c = u << 1 | rank(u << 1 | 1) < rank(u << 1)], a[u]), u = c;
        }
    }
};

struct Monster {
    int a, b;
    Monster(int ca = 0, int cb = 0) : a(ca), b(cb) {}
};

int n;

int Ta, Tb;
Monster Ma[N], Mb[N];

int Top;
int64 Topr, f[N];

Heap H;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1, a, b; i <= n; ++i) std::cin >> a >> b, (a <= b ? Ma[++Ta] : Mb[++Tb]) = Monster(a, b);
    std::sort(Ma + 1, Ma + Ta + 1, [](Monster x, Monster y) -> bool { return x.a < y.a; });
    std::sort(Mb + 1, Mb + Tb + 1, [](Monster x, Monster y) -> bool { return x.b < y.b; });
    for (int i = 1; i <= Tb; ++i) {
        int a = Mb[i].a, b = Mb[i].b;
        while (Topr && Topr <= b) {
            f[++Top] = Topr, Topr = 0;
            if (H.size()) Topr = f[Top] + H.top(), H.pop();
        }
        int64 nTopr = std::min(std::max(f[Top] - b, 0ll) + a, Topr ? Topr : INF64);
        if (!Topr) {
            Topr = nTopr;
        } else if (nTopr >= Topr) {
            H.insert(a - b);
        } else {
            H.insert((Topr - b + a) - nTopr), Topr = nTopr;
        }
    }
    if (Topr) f[++Top] = Topr;
    while (H.size()) f[Top + 1] = f[Top] + H.top(), ++Top, H.pop();
    int BTop = 1, ATop = 1;
    int64 Now = 0, AfterA = 0;
    for (int i = 1; i <= n; ++i) {
        int Aa = Ma[ATop].a, Ab = Ma[ATop].b;
        if (BTop > Tb || ATop <= Ta && Aa < f[BTop]) {
            Now += std::max(0ll, Aa - AfterA);
            AfterA += std::max(0ll, Aa - AfterA) + Ab - Aa;
            ++ATop;
        } else {
            Now += std::max(0ll, f[BTop] - AfterA);
            AfterA += std::max(0ll, f[BTop] - AfterA);
            ++BTop;
        }
        std::cout << Now << " \n"[i == n];
    }
    return 0;
}
