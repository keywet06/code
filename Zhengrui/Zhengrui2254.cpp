#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

inline int Add(int x, int y, int P) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y, int P) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y, int P) { return int64(x) * y % P; }

inline int Pow(int Base, int Exp, int P) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Ret = Mul(Ret, Base, P);
        Base = Mul(Base, Base, P), Exp >>= 1;
    }
    return Ret;
}

inline int BSGS(int x, int P) {
    const int S = 30000;
    int y = Pow(x, P - 2, P);
    std::unordered_map<int, int> Map;
    for (int c = y, i = 1; i < S; ++i, c = Mul(c, y, P)) {
        if (c == 1) return i;
        Map[c] = i;
    }
    int s = Pow(x, S, P);
    for (int c = s, i = S; ; i += S, c = Mul(c, s, P)) {
        if (c == 1) return i;
        if (Map.count(c)) return Map[c] + i;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n, m, p;
        std::cin >> n >> m >> p;
        if (p <= 5) {
            std::cout << (p == 2 || p == 5 ? 0ll : n / 3 * int64(m)) << std::endl;
            continue;
        }
        int x = BSGS(10, p);
        std::vector<std::pair<int, int> > Pri;
        int Max = 1;
        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                int c = 0;
                while (x % i == 0) ++c, x /= i;
                Pri.emplace_back(i, c), Max = std::max(Max, c);
            }
        }
        if (x > 1) Pri.emplace_back(x, 1);
        int64 Ans = 0;
        for (int y = 1; y <= Max && y <= m; ++y) {
            int t = n;
            for (auto p : Pri) {
                int d = p.first, c = p.second;
                c = (c + y - 1) / y;
                for (int i = 0; i < c; ++i) t /= d;
            }
            Ans += int64(t) * (y == Max ? m - Max + 1 : 1);
        }
        std::cout << Ans << '\n';
    }
    return 0;
}