#include <bits/stdc++.h>
struct data;
struct lazy;
struct point;
struct point {
    double x, y;
    int size;
};
struct lazy {
    double px, py, xx, xy, yx, yy;
};
struct data {
    point p;
    lazy l;
    data();
    data(point, lazy);
};
const double a = std::sqrt(3) / 2;
const double b = 1 - a;
const double c = 0.5;
const double d = 1 + a;
const double e = -a;
const int N = 100005;
const point empty_point({ 0.0, 0.0, 0 });
const lazy empty_lazy({ 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 });
data dt[N * 2];
int n, q, x, y, l, r;
point t;
point po[N];
std::istream &operator>>(std::istream &, point &);
std::ostream &operator<<(std::ostream &, point);
std::ostream &operator<<(std::ostream &, lazy);
std::ostream &operator<<(std::ostream &, data);
lazy operator*(lazy, lazy);
point operator*(lazy, point);
data operator*(lazy, data);
data &operator*=(data &, lazy);
point operator+(point, point);
point operator/(point, int);
lazy rotate60deg(point);
void pushup(int);
void pushdown(int);
void build(int, int, int);
point query(int, int, int, int, int);
void update(int, int, int, lazy, int, int);
void outall(int, int, int);
inline data::data() {}
inline data::data(point p, lazy l): p(p), l(l) {}
inline std::istream &operator>>(std::istream &in, point &p) {
    p.size = 1;
    return in >> p.x >> p.y;
}
inline std::ostream &operator<<(std::ostream &out, point p) {
    return out << "{" << p.x << ", " << p.y << ", " << p.size << "}";
}
inline std::ostream &operator<<(std::ostream &out, lazy l) {
    return out << "{" << l.px << ", " << l.py << ", "
      << l.xx << ", " << l.xy << ", "
      << l.yx << ", " << l.yy << "}";
}
inline std::ostream &operator<<(std::ostream &out, data d) {
    return out << "{" << d.p << ", " << d.l << "}";
}
inline lazy operator*(lazy x, lazy y) {
    return lazy({
        x.xx * y.px + x.xy * y.py + x.px,
        x.yx * y.px + x.yy * y.py + x.py,
        x.xx * y.xx + x.xy * y.yx,
        x.xx * y.xy + x.xy * y.yy,
        x.yx * y.xx + x.yy * y.yx,
        x.yx * y.xy + x.yy * y.yy
    });
}
inline point operator*(lazy x, point y) {
    return point({
        x.xx * y.x + x.xy * y.y + x.px * y.size,
        x.yx * y.x + x.yy * y.y + x.py * y.size,
        y.size
    });
}
inline data operator*(lazy x, data y) {
    return data(x * y.p, x * y.l);
}
inline data &operator*=(data &x, lazy y) { return x = y * x; }
inline point operator+(point x, point y) {
    return point({ x.x + y.x, x.y + y.y, x.size + y.size });
}
inline point operator/(point x, int y) {
    return point({ x.x / y, x.y / y, x.size / y });
}
inline lazy rotate60deg(point x) {
    return lazy({ c * x.x + d * x.y, b * x.x + c * x.y, c, e, a, c });
}
inline void pushup(int v) { dt[v].p = dt[v << 1].p + dt[v << 1 | 1].p; }
inline void pushdown(int v) {
    dt[v << 1] *= dt[v].l;
    dt[v << 1 | 1] *= dt[v].l;
    dt[v].l = empty_lazy;
}
inline void build(int v, int l, int r) {
    dt[v].l = empty_lazy;
    if (l == r) {
        dt[v].p = po[l];
        return;
    }
    int mid = l + r >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    pushup(v);
}
inline point query(int v, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return dt[v].p;
    }
    int mid = l + r >> 1;
    pushdown(v);
    return (x <= mid ? query(v << 1, x, y, l, mid) : empty_point) +
      (y > mid ? query(v << 1 | 1, x, y, mid + 1, r) : empty_point);
}
inline void update(int v, int x, int y, lazy z, int l, int r) {
    if (x <= l && r <= y) {
        // std::cout << "update " << dt[v] << "\n  mult " << z << "\n  to ";
        dt[v] *= z;
        // std::cout << dt[v] << "." << std::endl;
        return;
    }
    int mid = l + r >> 1;
    pushdown(v);
    if (x <= mid) {
        update(v << 1, x, y, z, l, mid);
    }
    if (y > mid) {
        update(v << 1 | 1, x, y, z, mid + 1, r);
    }
    pushup(v);
}
inline void outall(int v, int l, int r) {
    if (l == r) {
        std::cout << dt[v].p << std::endl;
        return;
    }
    int mid = l + r >> 1;
    pushdown(v);
    outall(v << 1, l, mid);
    outall(v << 1 | 1, mid + 1, r);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cout.setf(std::ios_base::fixed);
    std::cout.precision(10);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> po[i];
    }
    build(1, 1, n);
    for (int i = 1; i <= q; ++i) {
        std::cin >> x >> y;
        std::cout << (t = query(1, x, y, 1, n) / (y - x + 1)) << std::endl;
        std::cout << rotate60deg(t) << std::endl;
        std::cout << rotate60deg(t) * po[1] << std::endl;
        update(1, x, y, rotate60deg(t), 1, n);
    }
    outall(1, 1, n);
    return 0;
}