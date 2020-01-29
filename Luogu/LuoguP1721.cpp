#include <bits/stdc++.h>

namespace Decimal {

const int PREC = 3000;

class Decimal {
   public:
    Decimal();
    Decimal(const std::string &s);
    Decimal(const char *s);
    Decimal(int x);
    Decimal(long long x);
    Decimal(double x);

    bool is_zero() const;

    // p (p > 0) is the number of digits after the decimal point
    std::string to_string(int p) const;
    double to_double() const;

    friend Decimal operator+(const Decimal &a, const Decimal &b);
    friend Decimal operator+(const Decimal &a, int x);
    friend Decimal operator+(int x, const Decimal &a);
    friend Decimal operator+(const Decimal &a, long long x);
    friend Decimal operator+(long long x, const Decimal &a);
    friend Decimal operator+(const Decimal &a, double x);
    friend Decimal operator+(double x, const Decimal &a);

    friend Decimal operator-(const Decimal &a, const Decimal &b);
    friend Decimal operator-(const Decimal &a, int x);
    friend Decimal operator-(int x, const Decimal &a);
    friend Decimal operator-(const Decimal &a, long long x);
    friend Decimal operator-(long long x, const Decimal &a);
    friend Decimal operator-(const Decimal &a, double x);
    friend Decimal operator-(double x, const Decimal &a);

    friend Decimal operator*(const Decimal &a, int x);
    friend Decimal operator*(int x, const Decimal &a);

    friend Decimal operator/(const Decimal &a, int x);

    friend bool operator<(const Decimal &a, const Decimal &b);
    friend bool operator>(const Decimal &a, const Decimal &b);
    friend bool operator<=(const Decimal &a, const Decimal &b);
    friend bool operator>=(const Decimal &a, const Decimal &b);
    friend bool operator==(const Decimal &a, const Decimal &b);
    friend bool operator!=(const Decimal &a, const Decimal &b);

    Decimal &operator+=(int x);
    Decimal &operator+=(long long x);
    Decimal &operator+=(double x);
    Decimal &operator+=(const Decimal &b);

    Decimal &operator-=(int x);
    Decimal &operator-=(long long x);
    Decimal &operator-=(double x);
    Decimal &operator-=(const Decimal &b);

    Decimal &operator*=(int x);

    Decimal &operator/=(int x);

    friend Decimal operator-(const Decimal &a);

    // These can't be called
    friend Decimal operator*(const Decimal &a, double x);
    friend Decimal operator*(double x, const Decimal &a);
    friend Decimal operator/(const Decimal &a, double x);
    Decimal &operator*=(double x);
    Decimal &operator/=(double x);

   private:
    static const int len = PREC / 9 + 1;
    static const int mo = 1000000000;

    static void append_to_string(std::string &s, long long x);

    bool is_neg;
    long long integer;
    int data[len];

    void init_zero();
    void init(const char *s);
};

Decimal::Decimal() { this->init_zero(); }

Decimal::Decimal(const char *s) { this->init(s); }

Decimal::Decimal(const std::string &s) { this->init(s.c_str()); }

Decimal::Decimal(int x) {
    this->init_zero();

    if (x < 0) {
        is_neg = true;
        x = -x;
    }

    integer = x;
}

Decimal::Decimal(long long x) {
    this->init_zero();

    if (x < 0) {
        is_neg = true;
        x = -x;
    }

    integer = x;
}

Decimal::Decimal(double x) {
    this->init_zero();

    if (x < 0) {
        is_neg = true;
        x = -x;
    }

    integer = (long long)x;
    x -= integer;

    for (int i = 0; i < len; i++) {
        x *= mo;
        if (x < 0) x = 0;
        data[i] = (int)x;
        x -= data[i];
    }
}

void Decimal::init_zero() {
    is_neg = false;
    integer = 0;
    memset(data, 0, len * sizeof(int));
}

bool Decimal::is_zero() const {
    if (integer) return false;
    for (int i = 0; i < len; i++) {
        if (data[i]) return false;
    }
    return true;
}

void Decimal::init(const char *s) {
    this->init_zero();

    is_neg = false;
    integer = 0;

    // find the first digit or the negative sign
    while (*s != 0) {
        if (*s == '-') {
            is_neg = true;
            ++s;
            break;
        } else if (*s >= 48 && *s <= 57) {
            break;
        }
        ++s;
    }

    // read the integer part
    while (*s >= 48 && *s <= 57) {
        integer = integer * 10 + *s - 48;
        ++s;
    }

    // read the decimal part
    if (*s == '.') {
        int pos = 0;
        int x = mo / 10;

        ++s;
        while (pos < len && *s >= 48 && *s <= 57) {
            data[pos] += (*s - 48) * x;
            ++s;
            x /= 10;
            if (x == 0) {
                ++pos;
                x = mo / 10;
            }
        }
    }
}

void Decimal::append_to_string(std::string &s, long long x) {
    if (x == 0) {
        s.append(1, 48);
        return;
    }

    char _[30];
    int cnt = 0;
    while (x) {
        _[cnt++] = x % 10;
        x /= 10;
    }
    while (cnt--) {
        s.append(1, _[cnt] + 48);
    }
}

std::string Decimal::to_string(int p) const {
    std::string ret;

    if (is_neg && !this->is_zero()) {
        ret = "-";
    }

    append_to_string(ret, this->integer);

    ret.append(1, '.');

    for (int i = 0; i < len; i++) {
        // append data[i] as "%09d"
        int x = mo / 10;
        int tmp = data[i];
        while (x) {
            ret.append(1, 48 + tmp / x);
            tmp %= x;
            x /= 10;
            if (--p == 0) {
                break;
            }
        }
        if (p == 0) break;
    }

    if (p > 0) {
        ret.append(p, '0');
    }

    return ret;
}

double Decimal::to_double() const {
    double ret = integer;

    double k = 1.0;
    for (int i = 0; i < len; i++) {
        k /= mo;
        ret += k * data[i];
    }

    if (is_neg) {
        ret = -ret;
    }

    return ret;
}

bool operator<(const Decimal &a, const Decimal &b) {
    if (a.is_neg != b.is_neg) {
        return a.is_neg && (!a.is_zero() || !b.is_zero());
    } else if (!a.is_neg) {
        // a, b >= 0
        if (a.integer != b.integer) {
            return a.integer < b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] < b.data[i];
            }
        }
        return false;
    } else {
        // a, b <= 0
        if (a.integer != b.integer) {
            return a.integer > b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] > b.data[i];
            }
        }
        return false;
    }
}

bool operator>(const Decimal &a, const Decimal &b) {
    if (a.is_neg != b.is_neg) {
        return !a.is_neg && (!a.is_zero() || !b.is_zero());
    } else if (!a.is_neg) {
        // a, b >= 0
        if (a.integer != b.integer) {
            return a.integer > b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] > b.data[i];
            }
        }
        return false;
    } else {
        // a, b <= 0
        if (a.integer != b.integer) {
            return a.integer < b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] < b.data[i];
            }
        }
        return false;
    }
}

bool operator<=(const Decimal &a, const Decimal &b) {
    if (a.is_neg != b.is_neg) {
        return a.is_neg || (a.is_zero() && b.is_zero());
    } else if (!a.is_neg) {
        // a, b >= 0
        if (a.integer != b.integer) {
            return a.integer < b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] < b.data[i];
            }
        }
        return true;
    } else {
        // a, b <= 0
        if (a.integer != b.integer) {
            return a.integer > b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] > b.data[i];
            }
        }
        return true;
    }
}

bool operator>=(const Decimal &a, const Decimal &b) {
    if (a.is_neg != b.is_neg) {
        return !a.is_neg || (a.is_zero() && b.is_zero());
    } else if (!a.is_neg) {
        // a, b >= 0
        if (a.integer != b.integer) {
            return a.integer > b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] > b.data[i];
            }
        }
        return true;
    } else {
        // a, b <= 0
        if (a.integer != b.integer) {
            return a.integer < b.integer;
        }
        for (int i = 0; i < Decimal::len; i++) {
            if (a.data[i] != b.data[i]) {
                return a.data[i] < b.data[i];
            }
        }
        return true;
    }
}

bool operator==(const Decimal &a, const Decimal &b) {
    if (a.is_zero() && b.is_zero()) return true;
    if (a.is_neg != b.is_neg) return false;
    if (a.integer != b.integer) return false;
    for (int i = 0; i < Decimal::len; i++) {
        if (a.data[i] != b.data[i]) return false;
    }
    return true;
}

bool operator!=(const Decimal &a, const Decimal &b) { return !(a == b); }

Decimal &Decimal::operator+=(long long x) {
    if (!is_neg) {
        if (integer + x >= 0) {
            integer += x;
        } else {
            bool last = false;
            for (int i = len - 1; i >= 0; i--) {
                if (last || data[i]) {
                    data[i] = mo - data[i] - last;
                    last = true;
                } else {
                    last = false;
                }
            }
            integer = -x - integer - last;
            is_neg = true;
        }
    } else {
        if (integer - x >= 0) {
            integer -= x;
        } else {
            bool last = false;
            for (int i = len - 1; i >= 0; i--) {
                if (last || data[i]) {
                    data[i] = mo - data[i] - last;
                    last = true;
                } else {
                    last = false;
                }
            }
            integer = x - integer - last;
            is_neg = false;
        }
    }
    return *this;
}

Decimal &Decimal::operator+=(int x) { return *this += (long long)x; }

Decimal &Decimal::operator-=(int x) { return *this += (long long)-x; }

Decimal &Decimal::operator-=(long long x) { return *this += -x; }

Decimal &Decimal::operator/=(int x) {
    if (x < 0) {
        is_neg ^= 1;
        x = -x;
    }

    int last = integer % x;
    integer /= x;

    for (int i = 0; i < len; i++) {
        long long tmp = 1LL * last * mo + data[i];
        data[i] = tmp / x;
        last = tmp - 1LL * data[i] * x;
    }

    if (is_neg && integer == 0) {
        int i;
        for (i = 0; i < len; i++) {
            if (data[i] != 0) {
                break;
            }
        }
        if (i == len) {
            is_neg = false;
        }
    }

    return *this;
}

Decimal &Decimal::operator*=(int x) {
    if (x < 0) {
        is_neg ^= 1;
        x = -x;
    } else if (x == 0) {
        init_zero();
        return *this;
    }

    int last = 0;
    for (int i = len - 1; i >= 0; i--) {
        long long tmp = 1LL * data[i] * x + last;
        last = tmp / mo;
        data[i] = tmp - 1LL * last * mo;
    }
    integer = integer * x + last;

    return *this;
}

Decimal operator-(const Decimal &a) {
    Decimal ret = a;
    // -0 = 0
    if (!ret.is_neg && ret.integer == 0) {
        int i;
        for (i = 0; i < Decimal::len; i++) {
            if (ret.data[i] != 0) break;
        }
        if (i < Decimal::len) {
            ret.is_neg = true;
        }
    } else {
        ret.is_neg ^= 1;
    }
    return ret;
}

Decimal operator+(const Decimal &a, int x) {
    Decimal ret = a;
    return ret += x;
}

Decimal operator+(int x, const Decimal &a) {
    Decimal ret = a;
    return ret += x;
}

Decimal operator+(const Decimal &a, long long x) {
    Decimal ret = a;
    return ret += x;
}

Decimal operator+(long long x, const Decimal &a) {
    Decimal ret = a;
    return ret += x;
}

Decimal operator-(const Decimal &a, int x) {
    Decimal ret = a;
    return ret -= x;
}

Decimal operator-(int x, const Decimal &a) { return -(a - x); }

Decimal operator-(const Decimal &a, long long x) {
    Decimal ret = a;
    return ret -= x;
}

Decimal operator-(long long x, const Decimal &a) { return -(a - x); }

Decimal operator*(const Decimal &a, int x) {
    Decimal ret = a;
    return ret *= x;
}

Decimal operator*(int x, const Decimal &a) {
    Decimal ret = a;
    return ret *= x;
}

Decimal operator/(const Decimal &a, int x) {
    Decimal ret = a;
    return ret /= x;
}

Decimal operator+(const Decimal &a, const Decimal &b) {
    if (a.is_neg == b.is_neg) {
        Decimal ret = a;
        bool last = false;
        for (int i = Decimal::len - 1; i >= 0; i--) {
            ret.data[i] += b.data[i] + last;
            if (ret.data[i] >= Decimal::mo) {
                ret.data[i] -= Decimal::mo;
                last = true;
            } else {
                last = false;
            }
        }
        ret.integer += b.integer + last;
        return ret;
    } else if (!a.is_neg) {
        // a - |b|
        return a - -b;
    } else {
        // b - |a|
        return b - -a;
    }
}

Decimal operator-(const Decimal &a, const Decimal &b) {
    if (!a.is_neg && !b.is_neg) {
        if (a >= b) {
            Decimal ret = a;
            bool last = false;
            for (int i = Decimal::len - 1; i >= 0; i--) {
                ret.data[i] -= b.data[i] + last;
                if (ret.data[i] < 0) {
                    ret.data[i] += Decimal::mo;
                    last = true;
                } else {
                    last = false;
                }
            }
            ret.integer -= b.integer + last;
            return ret;
        } else {
            Decimal ret = b;
            bool last = false;
            for (int i = Decimal::len - 1; i >= 0; i--) {
                ret.data[i] -= a.data[i] + last;
                if (ret.data[i] < 0) {
                    ret.data[i] += Decimal::mo;
                    last = true;
                } else {
                    last = false;
                }
            }
            ret.integer -= a.integer + last;
            ret.is_neg = true;
            return ret;
        }
    } else if (a.is_neg && b.is_neg) {
        // a - b = (-b) - (-a)
        return -b - -a;
    } else if (a.is_neg) {
        // -|a| - b
        return -(-a + b);
    } else {
        // a - -|b|
        return a + -b;
    }
}

Decimal operator+(const Decimal &a, double x) { return a + Decimal(x); }

Decimal operator+(double x, const Decimal &a) { return Decimal(x) + a; }

Decimal operator-(const Decimal &a, double x) { return a - Decimal(x); }

Decimal operator-(double x, const Decimal &a) { return Decimal(x) - a; }

Decimal &Decimal::operator+=(double x) {
    *this = *this + Decimal(x);
    return *this;
}

Decimal &Decimal::operator-=(double x) {
    *this = *this - Decimal(x);
    return *this;
}

Decimal &Decimal::operator+=(const Decimal &b) {
    *this = *this + b;
    return *this;
}

Decimal &Decimal::operator-=(const Decimal &b) {
    *this = *this - b;
    return *this;
}

}  // namespace Decimal

const int N = 8000;
const int Np = N + 5;
const int O = 15;
class point;
class point {
   public:
    double x, y;
    point();
    point(double x, double y);
};
double max;
double f[O][Np];
int n, m, k, p, head, tail, id, limit;
int h[Np], sum[Np], q[Np];
int data[O][Np];
point pq[Np];
Decimal::Decimal ans;
double slope(point x, point y);
Decimal::Decimal calc(int x, int y);
inline point::point() {}
inline point::point(double a, double b) : x(a), y(b) {}
inline double slope(point x, point y) { return (x.y - y.y) / (x.x - y.x); }
Decimal::Decimal calc(int x, int y) {
    return y ? (calc(data[y][x], y - 1) + sum[x] - sum[data[y][x]]) /
      (x - data[y][x] + 1) : h[1];
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k >> p;
    for (int i = 1; i <= n; ++i) {
        std::cin >> h[i];
    }
    f[0][1] = h[1];
    std::sort(h + 1, h + n + 1);
    head = 1;
    while (h[head] < f[0][1]) {
        ++head;
    }
    for (int i = 1; i <= n - head + 1; ++i) {
        h[i] = h[i + head - 1];
    }
    n = n - head + 1;
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + h[i];
    }
    k = std::min(n, k);
    for (int i = 1; i <= n; ++i) {
        f[0][i] = h[1];
    }
    limit = std::min(O - 1, k);
    for (int l = 1; l <= limit; ++l) {
        q[head = tail = 1] = 1;
        for (int i = 1; i <= n; ++i) {
            pq[i] = point(i - 1.0, sum[i] - f[l - 1][i]);
        }
        for (int i = 2; i <= n; ++i) {
            point now = point(double(i), double(sum[i]));
            while (head < tail && slope(now, pq[q[head]]) < slope(now,
              pq[q[head + 1]])) {
                ++head;
            }
            data[l][i] = q[head];
            f[l][i] = (f[l - 1][q[head]] + sum[i] - sum[q[head]]) / (i -
              q[head] + 1);
            while (head < tail && slope(pq[q[tail]], pq[q[tail - 1]]) >
              slope(pq[q[tail]], pq[i])) {
                --tail;
            }
            q[++tail] = i;
        }
    }
    m = n - k + limit;
    for (int i = 0; i <= limit; ++i) {
        if (f[i][m] > max) {
            max = f[i][m];
            id = i;
        }
    }
    ans = calc(m, id);
    for (int i = m + 1; i <= n; ++i) {
        ans = (ans + h[i]) / 2;
    }
    std::cout << ans.to_string(p << 1) << std::endl;
    return 0;
}