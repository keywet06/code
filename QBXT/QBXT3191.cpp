#include <bits/stdc++.h>

inline int BPopC(int x) { return __builtin_popcount(x); }

const int P = 1000000007;

using int64 = long long;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Power(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Muls(Base, Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Power(x, P - 2); }

const int F = P - 1;

using Vector = std::vector<int>;
using Vector2 = std::vector<Vector>;

inline std::ostream &operator<<(std::ostream &out, Vector2 &Vec) {
    for (Vector &v : Vec) {
        for (int &x : v) out << x << ' ';
        out << std::endl;
    }
    return out;
}

inline int Det(Vector2 Mat) {
    size_t n = Mat.size();
    for (Vector &v : Mat) assert(v.size() == n);
    int Ans = 1;
    for (size_t i = 0, c = 0; i < n; c = ++i) {
        while (c + 1 < n && Mat[c][i] == 0) ++c;
        if (c != i) Mat[i].swap(Mat[c]), Muls(Ans, F);
        Muls(Ans, Mat[i][i]), c = Inv(Mat[i][i]);
        for (size_t j = i; j < n; ++j) Muls(Mat[i][j], c);
        for (size_t j = 0; j < n; ++j) {
            if (i == j) continue;
            c = P - Mat[j][i];
            for (size_t k = i; k < n; ++k) Adds(Mat[j][k], Mul(c, Mat[i][k]));
        }
    }
    return Ans;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int> > > Co(n - 1);
    for (int i = 0, k, x, y; i < n - 1; ++i) {
        std::cin >> k;
        while (k--) std::cin >> x >> y, Co[i].emplace_back(x - 2, y - 2);
    }
    int Ans = 0;
    for (int i = 0; i < 1 << n - 1; ++i) {
        Vector2 Mat(n - 1, Vector(n - 1));
        for (int j = 0; j < n - 1; ++j) {
            if ((i >> j) & 1) continue;
            for (auto [x, y] : Co[j]) {
                if (x >= 0) Adds(Mat[x][x], 1);
                if (y >= 0) Adds(Mat[y][y], 1);
                if (x >= 0 && y >= 0) Adds(Mat[x][y], F), Adds(Mat[y][x], F);
            }
        }
        Adds(Ans, Mul(Det(Mat), BPopC(i) & 1 ? F : 1));
    }
    std::cout << Ans << std::endl;
    return 0;
}