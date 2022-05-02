#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl;

using int64 = long long;

template <typename Type>
class Fenwick {
   protected:
    std::vector<Type> a;

   public:
    Fenwick() {}
    Fenwick(size_t n) : a(n + 1) {}
    void Resize(size_t n) { a = std::vector<Type>(n + 1); }
    void Add(size_t i, Type v) {
        while (i < a.size()) a[i] += v, i += i & -i;
    }
    Type Sum(size_t i) {
        Type Ret(0);
        while (i) Ret += a[i], i &= i - 1;
        return Ret;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, L, R;
    std::cin >> n >> L >> R;
    std::vector<int> a(n), DD(n + 3);
    DD[1] = n, DD[2] = -2 * n, DD[3] = n;
    Fenwick<int> Fen(n);
    for (int i = 0, x; i < n; ++i) {
        std::cin >> x;
        int c = i - Fen.Sum(x), d = n - x - c;
        ++DD[2], --DD[c + 2], ++DD[2], --DD[d + 2], Fen.Add(x, 1);
    }
    DD[3] -= n;
    for (int i = 3; i <= n + 2; ++i) ++DD[i];
    int64 D = 0, S = 0, Ans = 0;
    for (int i = 1; i <= R; ++i) S += D += DD[i], Ans ^= i >= L ? S : 0;
    std::cout << Ans << std::endl;
    return 0;
}