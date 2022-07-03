#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

#define templ template <typename Type1, typename Type2>
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : (x = y); }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return x > y ? x : (x = y); }
#undef templ

using int32 = int;
using int64 = long long;

struct RandomMachine {
    int32 x, a, b, c, d;
    RandomMachine() : x(0), a(0), b(0), c(0), d(1) {}
    RandomMachine(int32 X, int32 A, int32 B, int32 C, int32 D) : x(X), a(A), b(B), c(C), d(D) {}
    int32 Next() { return x = ((int64(a) * x + b) * x + c) % d; }
    int32 operator()() { return Next(); }
};

inline std::istream &operator>>(std::istream &In, RandomMachine &Machine) {
    return In >> Machine.x >> Machine.a >> Machine.b >> Machine.c >> Machine.d;
}

const int N = 5005;
const int Nd = N * N;
const int D = N * N;

int n, m, q, nm, QueTop;
int Min[N], Max[N], Te[D], RT[D], Que[Nd];

RandomMachine Rand;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> Rand >> n >> m >> q, nm = n * m;
    for (int i = 1; i <= nm; ++i) Te[i] = i, std::swap(Te[i], Te[Rand() % i + 1]);
    for (int i = 1, x, y; i <= q; ++i) std::cin >> x >> y, std::swap(Te[x], Te[y]);
    for (int i = 1; i <= nm; ++i) RT[Te[i]] = i - 1;
    for (int i = 1; i <= n; ++i) Min[i] = 1, Max[i] = m;
    for (int i = 1; i <= nm; ++i) {
        int x = RT[i] / m + 1, y = RT[i] % m + 1;
        // Debug << i << ": (" << x << ", " << y << ')' << std::endl;
        if (y < Min[x] || y > Max[x]) continue;
        Que[++QueTop] = i;
        for (int j = 1; j < x; ++j) Mid(Max[j], y);
        for (int j = x + 1; j <= n; ++j) Mad(Min[j], y);
    }
    for (int i = 1; i <= QueTop; ++i) std::cout << Que[i] << " \n"[i == QueTop];
    return 0;
}