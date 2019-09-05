#ifndef MATH_HPP
#define MATH_HPP
// Include:
// Declare:
namespace kw {
    int gcd(int, int);
}
// Implementation:
namespace kw {
    inline int gcd(int x, int y) {
        if (x % y == 0) {
            return y;
        }
        return gcd(y, x % y);
    }
}
#endif