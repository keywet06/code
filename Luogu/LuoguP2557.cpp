#include <bits/stdc++.h>

#define pub push_back
#define pob pop_back
#define fir first
#define sec second
#define ite iterator
#define reg register
#define mkp std::make_pair

using int32 = int;
using i5 = int32;
using pi5 = std::pair<i5, i5>;

namespace oct {

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
    int size();
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

inline BigInt::BigInt() { v.pub(0); }

inline BigInt::BigInt(int x) {
    if (!x) {
        v.pub(0);
    } else {
        while (x) v.pub(x % 10), x /= 10;
    }
}

inline BigInt::BigInt(long long x) {
    if (!x) {
        v.pub(0);
    } else {
        while (x) v.pub(x % 10), x /= 10;
    }
}

inline BigInt::BigInt(std::string s) {
    for (int i = s.size() - 1; ~i; --i) v.pub(s[i] - '0');
    zero();
}

inline BigInt::~BigInt() {}

inline void BigInt::in() {
    std::string s;
    std::cin >> s, *this = (BigInt)s;
}

inline void BigInt::out() {
    for (int i = size() - 1; ~i; --i) printf("%d", v[i]);
}

inline void BigInt::clear() { *this = (BigInt)0; }

inline int BigInt::size() { return v.size(); }

inline void BigInt::makelen(int x) {
    while (size() > x) v.pob();
    while (size() < x) v.pub(0);
}

inline void BigInt::zero() {
    while (!v[size() - 1] && size() > 1) v.pob();
}

inline void BigInt::carry() {
    for (int i = 0; i < size() - 1; ++i) v[i + 1] += v[i] / 10, v[i] %= 10;
    while (v[size() - 1] > 9) v.pub(v[size() - 1] / 10), v[size() - 2] %= 10;
    zero();
}

inline int& BigInt::operator[](int x) { return v[x]; }

inline int operator<(BigInt a, BigInt b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; ~i; --i) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return 0;
}

inline int operator<=(BigInt a, BigInt b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; ~i; --i) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return 1;
}

inline int operator>(BigInt a, BigInt b) { return !(a <= b); }

inline int operator>=(BigInt a, BigInt b) { return !(a < b); }

inline int operator==(BigInt a, BigInt b) {
    if (a.size() != b.size()) return 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

inline int operator!=(BigInt a, BigInt b) { return !(a == b); }

inline BigInt operator+(BigInt a, BigInt b) {
    BigInt c;
    if (a.size() < b.size()) {
        c = b;
        for (int i = 0; i < a.size(); ++i) c[i] += a[i];
        c.carry();
    } else {
        c = a;
        for (int i = 0; i < b.size(); ++i) c[i] += b[i];
        c.carry();
    }
    return c;
}

inline BigInt& operator+=(BigInt& a, BigInt b) { return a = a + b; }

inline BigInt operator-(BigInt a, BigInt b) {
    BigInt c = a;
    for (int i = 0; i < b.size(); ++i) {
        if (c[i] < b[i]) c[i] += 10, --c[i + 1];
        c[i] -= b[i];
    }
    for (int i = b.size(); i < a.size(); ++i) {
        if (c[i] >= 0) break;
        c[i] += 10, --c[i + 1];
    }
    c.zero();
    return c;
}

inline BigInt& operator-=(BigInt& a, BigInt b) { return a = a - b; }

inline BigInt operator*(BigInt a, BigInt b) {
    BigInt c;
    c.makelen(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) c[i + j] += a[i] * b[j];
    }
    c.carry();
    return c;
}

inline BigInt& operator*=(BigInt& a, BigInt b) { return a = a * b; }

inline BigInt operator/(BigInt a, int b) {
    BigInt c;
    int yu = 0;
    c.makelen(a.size());
    for (int i = a.size() - 1; ~i; --i) {
        yu = yu * 10 + a[i], c[i] = yu / b, yu %= b;
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
    for (int i = a.size() - 1; ~i; --i) ys = (ys * 10 + a[i]) % b;
    return ys;
}

inline std::istream& operator>>(std::istream& in, BigInt& a) {
    std::string s;
    in >> s, a = (BigInt)s;
    return in;
}

inline std::ostream& operator<<(std::ostream& out, BigInt a) {
    for (int i = a.size() - 1; ~i; --i) out << a[i];
    return out;
}

}  // namespace oct

int n, t, k;

std::vector<pi5> v;

oct::BigInt sum, mul, ans;

int main() {
    std::cin >> n >> k;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i) continue;
        t = 0;
        while (!(n % i)) ++t, n /= i;
        v.pub(mkp(i, t * k));
    }
    if (n != 1) v.pub(mkp(n, k));
    ans = 1;
    for (pi5 x : v) {
        sum = 1, mul = 1;
        for (int i = 0; i < x.sec; ++i) sum += mul *= x.fir;
        ans *= sum;
    }
    std::cout << ans << std::endl;
    return 0;
}