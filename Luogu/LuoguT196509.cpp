#ifndef KW_BIGINT_HPP
#define KW_BIGINT_HPP
// Include:
#ifndef STD_BITS_STDCPP_H
#define STD_BITS_STDCPP_H
#include <bits/stdc++.h>
#endif
// Declare:
namespace kw {
class BigInt {
   private:
    std::vector<int> v;

   public:
    BigInt();
    BigInt(int);
    BigInt(long long);
    BigInt(std::string);
    ~BigInt();
    void in();
    void out();
    void clear();
    int length();
    void makelen(int);
    void zero();
    void carry();
    int& operator[](int);
};
int operator<(BigInt, BigInt);
int operator<=(BigInt, BigInt);
int operator>(BigInt, BigInt);
int operator>=(BigInt, BigInt);
int operator==(BigInt, BigInt);
int operator!=(BigInt, BigInt);
BigInt operator+(BigInt, BigInt);
BigInt& operator+=(BigInt&, BigInt);
BigInt operator-(BigInt, BigInt);
BigInt& operator-=(BigInt&, BigInt);
BigInt operator*(BigInt, BigInt);
BigInt& operator*=(BigInt&, BigInt);
BigInt operator/(BigInt, int);
BigInt& operator/=(BigInt&, int);
int operator%(BigInt, int);
BigInt operator^(BigInt, int);
BigInt& operator^=(BigInt&, int);
std::istream& operator>>(std::istream&, BigInt&);
std::ostream& operator<<(std::ostream&, BigInt);
}  // namespace kw
// Implementation:
namespace kw {
inline BigInt::BigInt() { v.push_back(0); }
inline BigInt::BigInt(int x) {
    if (!x) {
        v.push_back(0);
    } else {
        while (x) {
            v.push_back(x % 10);
            x /= 10;
        }
    }
}
inline BigInt::BigInt(long long x) {
    if (!x) {
        v.push_back(0);
    } else {
        while (x) {
            v.push_back(x % 10);
            x /= 10;
        }
    }
}
inline BigInt::BigInt(std::string s) {
    for (int i = s.length() - 1; ~i; --i) {
        v.push_back(s[i] - '0');
    }
    zero();
}
inline BigInt::~BigInt() {}
inline void BigInt::in() {
    std::string s;
    std::cin >> s;
    *this = (BigInt)s;
}
inline void BigInt::out() {
    for (int i = length() - 1; ~i; --i) {
        printf("%d", v[i]);
    }
}
inline void BigInt::clear() { *this = (BigInt)0; }
inline int BigInt::length() { return v.size(); }
inline void BigInt::makelen(int x) {
    while (length() > x) {
        v.pop_back();
    }
    while (length() < x) {
        v.push_back(0);
    }
}
inline void BigInt::zero() {
    while (!v[length() - 1] && length() > 1) {
        v.pop_back();
    }
}
inline void BigInt::carry() {
    for (int i = 0; i < length() - 1; ++i) {
        v[i + 1] += v[i] / 10;
        v[i] %= 10;
    }
    while (v[length() - 1] > 9) {
        v.push_back(v[length() - 1] / 10);
        v[length() - 2] %= 10;
    }
    zero();
}
inline int& BigInt::operator[](int x) { return v[x]; }
inline int operator<(BigInt a, BigInt b) {
    if (a.length() != b.length()) {
        return a.length() < b.length();
    }
    for (int i = a.length() - 1; ~i; --i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return 0;
}
inline int operator<=(BigInt a, BigInt b) {
    if (a.length() != b.length()) {
        return a.length() < b.length();
    }
    for (int i = a.length() - 1; ~i; --i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return 1;
}
inline int operator>(BigInt a, BigInt b) { return !(a <= b); }
inline int operator>=(BigInt a, BigInt b) { return !(a < b); }
inline int operator==(BigInt a, BigInt b) {
    if (a.length() != b.length()) {
        return 0;
    }
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
inline int operator!=(BigInt a, BigInt b) { return !(a == b); }
inline BigInt operator+(BigInt a, BigInt b) {
    BigInt c;
    if (a.length() < b.length()) {
        c = b;
        for (int i = 0; i < a.length(); ++i) {
            c[i] += a[i];
        }
        c.carry();
    } else {
        c = a;
        for (int i = 0; i < b.length(); ++i) {
            c[i] += b[i];
        }
        c.carry();
    }
    return c;
}
inline BigInt& operator+=(BigInt& a, BigInt b) { return a = a + b; }
inline BigInt operator-(BigInt a, BigInt b) {
    BigInt c = a;
    for (int i = 0; i < b.length(); ++i) {
        if (c[i] < b[i]) {
            c[i] += 10;
            --c[i + 1];
        }
        c[i] -= b[i];
    }
    for (int i = b.length(); i < a.length(); ++i) {
        if (c[i] < 0) {
            c[i] += 10;
            --c[i + 1];
        } else {
            break;
        }
    }
    c.zero();
    return c;
}
inline BigInt& operator-=(BigInt& a, BigInt b) { return a = a - b; }
inline BigInt operator*(BigInt a, BigInt b) {
    BigInt c;
    c.makelen(a.length() + b.length() - 1);
    for (int i = 0; i < a.length(); ++i) {
        for (int j = 0; j < b.length(); ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
    c.carry();
    return c;
}
inline BigInt& operator*=(BigInt& a, BigInt b) { return a = a * b; }
inline BigInt operator/(BigInt a, int b) {
    BigInt c;
    int yu = 0;
    c.makelen(a.length());
    for (int i = a.length() - 1; ~i; --i) {
        yu = yu * 10 + a[i];
        c[i] = yu / b;
        yu %= b;
    }
    c.zero();
    return c;
}
inline BigInt& operator/=(BigInt& a, int b) { return a = a / b; }
inline BigInt operator^(BigInt a, long long b) {
    return b ? ((a * a) ^ (b / 2)) * (b & 1 ? a : 1) : 1;
}
inline BigInt& operator^=(BigInt& a, long long b) { return a = (a ^ b); }
inline int operator%(BigInt a, int b) {
    long long ys = 0;
    for (int i = a.length() - 1; ~i; --i) {
        ys = (ys * 10 + a[i]) % b;
    }
    return ys;
}
std::istream& operator>>(std::istream& in, BigInt& a) {
    std::string s;
    in >> s;
    a = (BigInt)s;
    return in;
}
std::ostream& operator<<(std::ostream& out, BigInt a) {
    for (int i = a.length() - 1; ~i; --i) {
        out << a[i];
    }
    return out;
}
}  // namespace kw
#endif

int main() {
    kw::BigInt n, x, ans;
    std::cin >> n, x = n / 2 - 1;
    if (n < 4) return std::cout << 0 << std::endl, 0;
    ans += 2 * x * (x * x - 1) / 3;
    ans += x * (x + 1) / 2 * (n[0] & 1 ? 3 : 1);
    if (n < 6) return std::cout << ans << std::endl, 0;
    x = (n - 1) / 6;
    ans += x * (x + 1) * (2 * x + 1) / 2 - x * (x + 1) / 2 * 2;
    x = (n - 2) / 6;
    ans += x * (x + 1) * (2 * x + 1) / 2 - x * (x + 1) / 2;
    x = (n - 3) / 6;
    ans += x * (x + 1) * (2 * x + 1) / 2;
    x = (n - 4) / 6;
    ans += x * (x + 1) * (2 * x + 1) / 2 + x * (x + 1) / 2 * 1;
    x = (n - 5) / 6;
    ans += x * (x + 1) * (2 * x + 1) / 2 + x * (x + 1) / 2 * 2;
    x = (n - 6) / 6;
    ans += x * (x + 1) * (2 * x + 1) / 2 + x * (x + 1) / 2 * 3 + (x + 1);
    std::cout << ans << std::endl;
    return 0;
}