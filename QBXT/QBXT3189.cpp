#include <bits/stdc++.h>

using int64 = long long;

const int P = 1000000007;

inline int Add(int a, int b) { return (a += b) >= P ? (a -= P) : a; }
inline int Mul(int a, int b) { return int64(a) * b % P; }

inline int &Adds(int &a, int b) { return (a += b) >= P ? (a -= P) : a; }
inline int &Muls(int &a, int b) { return a = int64(a) * b % P; }

inline int Power(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Muls(Base, Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Power(x, P - 2); }

inline std::ostream &operator<<(std::ostream &out,
                                std::vector<std::vector<int> > Vec) {
    for (auto v : Vec) {
        for (auto x : v) out << (x > P / 2 ? -(P - x) : x) << ' ';
        out << std::endl;
    }
    return out;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n, --n;
    std::vector<std::vector<int> > Mat(n, std::vector<int>(n));
    for (int i = 0; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j <= n; ++j) {
            if (s[j] == '1') {
                if (j) Adds(Mat[j - 1][j - 1], 1);
                if (i && j) Adds(Mat[i - 1][j - 1], P - 1);
            }
        }
    }
    int Ans = 1;
    for (int i = 0, c = 0; i < n; c = ++i) {
        while (c + 1 < n && Mat[c][i] == 0) ++c;
        if (c != i) Mat[c].swap(Mat[i]), Muls(Ans, P - 1);
        Muls(Ans, Mat[i][i]), c = Inv(Mat[i][i]);
        for (int j = i; j < n; ++j) Muls(Mat[i][j], c);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            c = P - Mat[j][i];
            for (int k = i; k < n; ++k) Adds(Mat[j][k], Mul(Mat[i][k], c));
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}