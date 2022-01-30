#include <bits/stdc++.h>

using ldou = long double;

struct Point {
    ldou x, y;
    Point() : x(0), y(0) {}
    Point(ldou X, ldou Y) : x(X), y(Y) {}
};

inline std::istream &operator>>(std::istream &in, Point &A) {
    return in >> A.x >> A.y;
}

inline Point operator*(ldou k, Point A) { return Point(k * A.x, k * A.y); }

inline Point operator*(Point A, ldou k) { return Point(k * A.x, k * A.y); }

inline Point operator/(Point A, ldou k) { return Point(A.x / k, A.y / k); }

inline Point operator+(Point A, Point B) { return Point(A.x + B.x, A.y + B.y); }

inline Point operator-(Point A, Point B) { return Point(A.x - B.x, A.y - B.y); }

inline ldou operator^(Point A, Point B) { return A.x * B.x + A.y * B.y; }

inline ldou operator*(Point A, Point B) { return A.x * B.y - A.y * B.x; }

inline Point And(Point La, Point Lb, Point Ma, Point Mb) {
    ldou x = (Ma - La) * (Lb - La), y = (Lb - La) * (Mb - La);
    return (x * Mb + y * Ma) / (x + y);
}

struct Edge {
    Point A, B;
    Edge() {}
    Edge(Point a, Point b) : A(a), B(b) {}
    Edge(ldou Ax, ldou Ay, ldou Bx, ldou By) : A(Ax, Ay), B(Bx, By) {}
    bool Smaller(Point C, Point D) {
        return (D.x - C.x) * (B.x - A.x) > 0 || (D.y - C.y) * (B.y - A.y) > 0;
    }
};

inline std::istream &operator>>(std::istream &in, Edge &L) {
    return in >> L.A >> L.B;
}

inline Point And(Edge L, Edge M) { return And(L.A, L.B, M.A, M.B); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Edge> Ed(n);
    for (int i = 0; i < n; ++i) std::cin >> Ed[i];
    std::sort(Ed.begin(), Ed.end(), [](Edge L, Edge M) -> bool {
        bool a = Point(1, 0) * (L.B - L.A) > 0,
             b = Point(1, 0) * (M.B - M.A) > 0;
        return a == b ? (L.B - L.A) * (M.B - M.A) > 0 : a > b;
    });
    std::deque<Edge> Deq;
    for (Edge x : Ed) {
        if (Deq.size() < 2) {
            Deq.push_back(x);
        } else {
            while (true) {
                Edge a = Deq.rbegin()[1], b = Deq.back();
            }
        }
    }
    return 0;
}