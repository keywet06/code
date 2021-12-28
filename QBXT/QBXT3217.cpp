#include <bits/stdc++.h>

template <typename Type>
inline Type Sqr(Type x) {
    return x * x;
}

const double O = 1e-8;

struct Point {
    double x, y;
    inline Point(){};
    inline Point(double X, double Y) : x(X), y(Y) {}
};

inline bool operator<(Point a, Point b) {
    return std::abs(a.x - b.x) < O ? a.y < b.y : a.x < b.x;
}

inline Point operator-(Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }

inline double operator^(Point a, Point b) { return a.x * b.y - b.x * a.y; }

inline std::istream &operator>>(std::istream &in, Point &a) {
    return in >> a.x >> a.y;
}

inline bool TurnRight(Point a, Point b, Point c) {
    return ((b - a) ^ (c - b)) < 0;
}

inline double Dis(Point a, Point b) {
    return sqrt(Sqr(a.x - b.x) + Sqr(a.y - b.y));
}

const int N = 100000;

int Top;

Point a[N], Que[N];

inline void Add(int Id) {
    while (Top > 1 && !TurnRight(Que[Top - 2], Que[Top - 1], a[Id])) --Top;
    Que[Top++] = a[Id];
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout << std::fixed << std::setprecision(6);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::sort(a, a + n);
    double Ans = 0;
    for (int i = 0; i < n; ++i) Add(i);
    for (int i = 1; i < Top; ++i) Ans += Dis(Que[i - 1], Que[i]);
    Top = 0;
    for (int i = n - 1; i >= 0; --i) Add(i);
    for (int i = 1; i < Top; ++i) Ans += Dis(Que[i - 1], Que[i]);
    std::cout << Ans << '\n';
    return 0;
}