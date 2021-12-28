#include <bits/stdc++.h>

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double X, double Y) : x(X), y(Y) {}
};

inline Point operator+(Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

inline Point operator-(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

inline Point operator*(double k, Point a) {
    return Point(k * a.x, k * a.y);
}

inline Point operator/(Point a, double k) {
    return Point(a.x / k, a.y / k);
}

inline std::istream &operator>>(std::istream &in, Point &a) {
    return in >> a.x >> a.y;
}

inline std::ostream &operator<<(std::ostream &out, Point a) {
    return out << a.x << ' ' << a.y;
}

inline double operator^(Point a, Point b) {
    return a.x * b.y - b.x * a.y;
}

inline Point Inter(Point a1, Point a2, Point b1, Point b2) {
    double S1 = (a1 - b1) ^ (b2 - b1);
    double S2 = (b2 - b1) ^ (a2 - b1);
    return (S2 * a1 + S1 * a2) / (S1 + S2);
}

Point a, b, c, d;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout << std::fixed << std::setprecision(6);
    std::cin >> a >> b >> c >> d;
    std::cout << Inter(a, b, c, d) << '\n';
    return 0;
}