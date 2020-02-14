#include <bits/stdc++.h>
const double eps = 1e-6;
const double pi = 3.141592653589793238462643383279502884;
const int N = 30;
typedef std::pair<double, double> point;
double ans1, ans2, R;
double al[N], h[N], a[N], b[N], c[N];
int n;
std::vector<point> ps, ks, vs;
int sgn(double x);
template <typename __Tp>
__Tp sqr(__Tp x);
std::ostream &operator<<(std::ostream &out, point x);
point operator-(point x, point y);
double operator*(point x, point y);
int ons(point x);
double dis(point x, point y);
inline int sgn(double x) { return std::abs(x) < eps ? 0 : ((x > 0) << 1) - 1; }
template <typename __Tp>
inline __Tp sqr(__Tp x) {
    return x * x;
}
inline std::ostream &operator<<(std::ostream &out, point x) {
    return out << "(" << x.first << ", " << x.second << ")";
}
inline point operator-(point x, point y) {
    return std::make_pair(y.first - x.first, y.second - x.second);
}
inline double operator*(point x, point y) {
    return x.first * y.second - x.second * y.first;
}
inline int ons(point x) {
    return sgn(sqr(x.first) + sqr(x.second) - sqr(R)) == 0;
}
inline double dis(point x, point y) {
    return sqrt(sqr(x.first - y.first) + sqr(x.second - y.second));
}
inline double to(double x) { return sgn(x) < 0 ? x + 2 * pi : x; }
int main() {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(10);
    std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(10);
    std::cin >> n >> R;
    for (int i = 0; i < n; ++i) {
        std::cin >> al[i] >> h[i];
        if (!sgn(h[i] - R)) {
            --i;
            --n;
            continue;
        }
        // al[i] += 123.45678;
        if (al[i] >= 360) {
            al[i] -= 360;
        }
        al[i] = al[i] / 180 * pi;
        a[i] = -1 / tan(al[i]);
        b[i] = -1;
        c[i] = h[i] / sin(al[i]);
        std::cerr << "Debug: " << a[i] << "x + " << b[i] << "y + " << c[i]
                  << " = 0" << std::endl;
        double tmp =
            sqrt(sqr(a[i] * c[i]) - (sqr(a[i]) + 1) * (sqr(c[i]) - sqr(R)));
        std::cout << tmp << std::endl;
        point s;
        ps.push_back(
            s = std::make_pair(
                (-a[i] * c[i] + tmp) / (sqr(a[i]) + 1),
                a[i] * ((-a[i] * c[i] + tmp) / (sqr(a[i]) + 1)) + c[i]));
        std::cerr << "Debug: " << s << " ";
        ps.push_back(
            s = std::make_pair(
                (-a[i] * c[i] - tmp) / (sqr(a[i]) + 1),
                a[i] * ((-a[i] * c[i] - tmp) / (sqr(a[i]) + 1)) + c[i]));
        std::cerr << s << std::endl;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (!sgn(std::abs(al[i] - al[j]) - pi)) {
                continue;
            }
            point p;
            p.first = (c[i] - c[j]) / (a[j] - a[i]);
            p.second = p.first * a[i] + c[i];
            ps.push_back(p);
            if (sgn(sqr(p.first) + sqr(p.second) - sqr(R)) == 1) {
                continue;
            }
            double alpha = atan(p.second / p.first),
                   beta = acos(R / sqrt(sqr(p.first) + sqr(p.second)));
            ps.push_back(
                std::make_pair(R * cos(alpha + beta), R * sin(alpha + beta)));
            ps.push_back(
                std::make_pair(R * cos(alpha - beta), R * sin(alpha - beta)));
        }
    }
    for (int i = 0; i < ps.size(); ++i) {
        ks.push_back(std::make_pair(
            sqr(R) * ps[i].first / (sqr(ps[i].first) + sqr(ps[i].second)),
            sqr(R) * ps[i].second / (sqr(ps[i].first) + sqr(ps[i].second))));
    }
    std::sort(ks.begin(), ks.end());
    vs.push_back(ks[0]);
    for (int i = 1; i < ks.size(); ++i) {
        while (vs.size() > 1 && sgn((vs[vs.size() - 1] - vs[vs.size() - 2]) *
                                    (ks[i] - vs[vs.size() - 1])) != 1) {
            vs.pop_back();
        }
        vs.push_back(ks[i]);
    }
    for (int i = ks.size() - 1; i; --i) {
        while (vs.size() > 1 && sgn((vs[vs.size() - 1] - vs[vs.size() - 2]) *
                                    (ks[i] - vs[vs.size() - 1])) != 1) {
            vs.pop_back();
        }
        vs.push_back(ks[i]);
    }
    vs.push_back(ks[0]);
    for (int i = 0; i < vs.size(); ++i) {
        vs[i] = std::make_pair(
            sqr(R) * vs[i].first / (sqr(vs[i].first) + sqr(vs[i].second)),
            sqr(R) * vs[i].second / (sqr(vs[i].first) + sqr(vs[i].second)));
        std::cerr << "Debug: " << vs[i] << std::endl;
    }
    for (int i = 0; i < vs.size() - 1; ++i) {
        std::cerr << "Debug: " << "ans[2] = " << ans1 << " " << ans2 << std::endl;
        std::cerr << "Debug: " << vs[i] << " " << vs[i + 1] << " " << dis(vs[i], vs[i + 1]) << std::endl;
        if (!ons(vs[i]) || !ons(vs[i + 1])) {
            ans1 += dis(vs[i], vs[i + 1]);
            continue;
        }
        double as = (vs[i].second - vs[i + 1].second) /
                    (vs[i].first - vs[i + 1].first),
               bs = -1, cs = vs[i].second - vs[i].first * as;
        std::cerr << "Debug: " << as << "x + " << bs << "y + " << cs << " = 0"
                  << std::endl;
        int flag = 1;
        for (int j = 0; j < n; ++j) {
            if (sgn(as - a[j]) == 0 && sgn(cs - c[j]) == 0 &&
                !(n == 1 && i == 0)) {
                flag = 0;
                ans1 += dis(vs[i], vs[i + 1]);
                break;
            }
        }
        if (flag) {
            std::cerr << "Debug: hu: " << asin(vs[i + 1].second / vs[i + 1].first) << " " << asin(vs[i].second / vs[i].first) << std::endl;
            ans2 += R * to(atan(vs[i].second / vs[i].first) - atan(vs[i + 1].second / vs[i + 1].first));
        }
    }
    std::cout << ans1 << " " << ans2 << std::endl;
    return 0;
}