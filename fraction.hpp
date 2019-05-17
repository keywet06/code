#ifndef FRACTION_HPP
#define FRACTION_HPP
// include:
#include <bits/stdc++.h>

// Declare:
namespace kw {
    template<typename T> class fraction {
        private:
            T gcd(T, T);
            T lcm(T, T);
        public:
            T fx, fy;
            fraction<T>();
            fraction<T>(T);
            fraction<T>(T, T);
            void update();
    };
    template<typename T> fraction<T> operator+(fraction<T>, fraction<T>);
    template<typename T> fraction<T> operator-(fraction<T>, fraction<T>);
    template<typename T> fraction<T> operator*(fraction<T>, fraction<T>);
    template<typename T> fraction<T> operator/(fraction<T>, fraction<T>);
    template<typename T> fraction<T>& operator+=(fraction<T>&, fraction<T>);
    template<typename T> fraction<T>& operator-=(fraction<T>&, fraction<T>);
    template<typename T> fraction<T>& operator*=(fraction<T>&, fraction<T>);
    template<typename T> fraction<T>& operator/=(fraction<T>&, fraction<T>);
    template<typename T> T operator<(fraction<T>, fraction<T>);
    template<typename T> T operator<=(fraction<T>, fraction<T>);
    template<typename T> T operator>(fraction<T>, fraction<T>);
    template<typename T> T operator>=(fraction<T>, fraction<T>);
    template<typename T> T operator==(fraction<T>, fraction<T>);
    template<typename T> T operator!=(fraction<T>, fraction<T>);
}  // namespace kw

// Implementation:
namespace kw {
    template<typename T> inline T fraction<T>::gcd(T x, T y) {
        if (y == 0) {
            return x;
        }
        return gcd(y, x % y);
    }
    template<typename T> inline T fraction<T>::lcm(T x, T y) { return x * y / gcd(x, y); }
    template<typename T> inline fraction<T>::fraction<T>() { fx = fy = 1; }
    template<typename T> inline fraction<T>::fraction<T>(T x) {
        fx = x;
        fy = 1;
    }
    template<typename T> inline fraction<T>::fraction<T>(T x, T y) {
        fx = x;
        fy = y;
    }
    template<typename T> inline void fraction<T>::update() {
        T tmp = gcd(fx, fy);
        fx /= tmp;
        fy /= tmp;
    }
    template<typename T> inline fraction<T> operator+(fraction<T> a, fraction<T> b) {
        fraction<T> c(a.fx * b.fy + a.fy * b.fx, a.fy * b.fy);
        c.update();
        return c;
    }
    template<typename T> inline fraction<T> operator-(fraction<T> a, fraction<T> b) {
        fraction<T> c(a.fx * b.fy - a.fy * b.fx, a.fy * b.fy);
        c.update();
        return c;
    }
    template<typename T> inline fraction<T> operator*(fraction<T> a, fraction<T> b) {
        fraction<T> c(a.fx * b.fx, a.fy * b.fy);
        c.update();
        return c;
    }
    template<typename T> inline fraction<T> operator/(fraction<T> a, fraction<T> b) {
        fraction<T> c(a.fx * b.fy, a.fy * b.fx);
        c.update();
        return c;
    }
    template<typename T> inline fraction<T>& operator+=(fraction<T>& a, fraction<T> b) { return a = a + b; }
    template<typename T> inline fraction<T>& operator-=(fraction<T>& a, fraction<T> b) { return a = a - b; }
    template<typename T> inline fraction<T>& operator*=(fraction<T>& a, fraction<T> b) { return a = a * b; }
    template<typename T> inline fraction<T>& operator/=(fraction<T>& a, fraction<T> b) { return a = a / b; }
    template<typename T> inline T operator<(fraction<T> a, fraction<T> b) { return a.fx * b.fy < a.fy * b.fx; }
    template<typename T> inline T operator<=(fraction<T> a, fraction<T> b) { return a.fx * b.fy <= a.fy * b.fx; }
    template<typename T> inline T operator>(fraction<T> a, fraction<T> b) { return a.fx * b.fy > a.fy * b.fx; }
    template<typename T> inline T operator>=(fraction<T> a, fraction<T> b) { return a.fx * b.fy >= a.fy * b.fx; }
    template<typename T> inline T operator==(fraction<T> a, fraction<T> b) { return a.fx * b.fy == a.fy * b.fx; }
    template<typename T> inline T operator!=(fraction<T> a, fraction<T> b) { return a.fx * b.fy != a.fy * b.fx; }
}  // namespace kw
#endif