#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

inline std::ostream &operator<<(std::ostream &out,
                                std::vector<std::vector<int> > Vec) {
    for (auto &v : Vec) {
        for (int x : v) out << x << ' ';
        out << std::endl;
    }
    return out;
}

using int64 = long long;

const int P = 1000000007;
const int F = P - 1;

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

const int INF = 10000;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::vector<int> > Edge(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> Edge[i][j];
            if (Edge[i][j] == 0 && i != j) Edge[i][j] = INF;
        }
    }
    std::vector<std::vector<int> > Dis(Edge);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) Mid(Dis[i][j], Dis[i][k] + Dis[k][j]);
        }
    }
    std::vector<std::vector<int> > Mat(n - 1, std::vector<int>(n - 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (Dis[0][i] + Edge[i][j] == Dis[0][j]) {
                if (j) Adds(Mat[j - 1][j - 1], 1);
                if (i && j) Adds(Mat[i - 1][j - 1], F);
            }
        }
    }
    --n;
    int Ans = 1;
    for (int i = 0, c = 0; i < n; c = ++i) {
        while (c + 1 < n && Mat[c][i] == 0) ++c;
        if (c != i) Mat[i].swap(Mat[c]), Muls(Ans, F);
        c = Inv(Mat[i][i]), Muls(Ans, Mat[i][i]);
        for (int j = i; j < n; ++j) Muls(Mat[i][j], c);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            c = Mat[j][i];
            for (int k = i; k < n; ++k) Adds(Mat[j][k], P - Mul(c, Mat[i][k]));
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}