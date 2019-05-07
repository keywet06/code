#ifndef FRACTION_HPP
#define FRACTION_HPP
// include:
#include <bits/stdc++.h>

// Declare:
namespace kw {
    class fraction {
        private:
            int gcd(int, int);
            int lcm(int, int);
        public:
            int fx, fy;
            fraction();
            fraction(int);
            fraction(int, int);
            void update();
    };
    fraction operator+(fraction, fraction);
    fraction operator-(fraction, fraction);
    fraction operator*(fraction, fraction);
    fraction operator/(fraction, fraction);
    int operator<(fraction, fraction);
    int operator<=(fraction, fraction);
    int operator>(fraction, fraction);
    int operator>=(fraction, fraction);
    int operator==(fraction, fraction);
    int operator!=(fraction, fraction);
}  // namespace kw

// Implementation:
namespace kw {
    inline int fraction::gcd(int x, int y) {
        if (y == 0) {
            return x;
        }
        return gcd(y, x % y);
    }
    inline int fraction::lcm(int x, int y) { return x * y / gcd(x, y); }
    inline fraction::fraction() { fx = fy = 1; }
    inline fraction::fraction(int x) {
        fx = x;
        fy = 1;
    }
    inline fraction::fraction(int x, int y) {
        fx = x;
        fy = y;
    }
    inline void fraction::update() {
        int tmp = gcd(fx, fy);
        fx /= tmp;
        fy /= tmp;
    }
    inline fraction operator+(fraction a, fraction b) {
        fraction c(a.fx * b.fy + a.fy * b.fx, a.fy * b.fy);
        c.update();
        return c;
    }
    inline fraction operator-(fraction a, fraction b) {
        fraction c(a.fx * b.fy - a.fy * b.fx, a.fy * b.fy);
        c.update();
        return c;
    }
    inline fraction operator*(fraction a, fraction b) {
        fraction c(a.fx * b.fx, a.fy * b.fy);
        c.update();
        return c;
    }
    inline fraction operator/(fraction a, fraction b) {
        fraction c(a.fx * b.fy, a.fy * b.fx);
        c.update();
        return c;
    }
    inline int operator<(fraction a, fraction b) { return a.fx * b.fy < a.fy * b.fx; }
    inline int operator<=(fraction a, fraction b) { return a.fx * b.fy <= a.fy * b.fx; }
    inline int operator>(fraction a, fraction b) { return a.fx * b.fy > a.fy * b.fx; }
    inline int operator>=(fraction a, fraction b) { return a.fx * b.fy >= a.fy * b.fx; }
    inline int operator==(fraction a, fraction b) { return a.fx * b.fy == a.fy * b.fx; }
    inline int operator!=(fraction a, fraction b) { return a.fx * b.fy != a.fy * b.fx; }
}  // namespace kw
#endif