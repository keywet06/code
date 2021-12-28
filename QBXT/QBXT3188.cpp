#include <bits/stdc++.h>

class BigInt {
   protected:
    std::vector<int> Data;

   public:
    inline BigInt() : Data(1, 0) {}
    inline BigInt(int x) {
        if (!x) Data.push_back(0);
        while (x) Data.push_back(x % 10), x /= 10;
    }
    inline int &operator[](size_t Id) { return Data[Id]; }
    inline int &back() { return Data.back(); }
    inline size_t size() { return Data.size(); }
    inline void resize(size_t s) { Data.resize(s, 0); }
    inline void push(int x) { Data.push_back(x); }
    inline void pop() { Data.pop_back(); }
};

inline BigInt operator+(BigInt a, BigInt b) {
    if (a.size() < b.size()) std::swap(a, b);
    a[0] += b[0];
    for (int i = 1; i < b.size(); ++i) {
        a[i] += b[i] + a[i - 1] / 10, a[i - 1] %= 10;
    }
    for (int i = b.size(); i + 1 < a.size(); ++i) {
        if (a[i] < 10) break;
        a[i + 1] += a[i] / 10, a[i] %= 10;
    }
    for (int i = a.size() - 1; a[i] >= 10; ++i) {
        a[i] %= 10, a.push(1);
    }
    return a;
}

inline BigInt operator-(BigInt a, BigInt b) {
    for (int i = 0; i < b.size(); ++i) {
        if ((a[i] -= b[i]) < 0) a[i] += 10, --a[i + 1];
    }
    for (int i = b.size(); i < a.size() && a[i] < 0; ++i) {
        a[i] += 10, --a[i + 1];
    }
    while (a.size() > 1 && a.back() == 0) a.pop();
    return a;
}

inline BigInt operator*(int x, BigInt b) {
    b[0] *= x;
    for (int i = 1; i < b.size(); ++i) {
        (b[i] *= x) += b[i - 1] / 10, b[i - 1] %= 10;
    }
    for (int i = b.size() - 1; b[i] >= 10; ++i) {
        b.push(b[i] / 10), b[i] %= 10;
    }
    return b;
}

inline std::ostream &operator<<(std::ostream &out, BigInt x) {
    for (int i = x.size() - 1; i >= 0; --i) out << x[i];
    return out;
}

inline BigInt operator*(BigInt a, BigInt b) {
    BigInt Ret;
    Ret.resize(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) Ret[i + j] += a[i] * b[j];
    }
    for (int i = 1; i < Ret.size(); ++i) {
        Ret[i] += Ret[i - 1] / 10, Ret[i - 1] %= 10;
    }
    while (Ret.back() >= 10) {
        Ret.push(Ret.back() / 10), Ret[Ret.size() - 2] %= 10;
    }
    return Ret;
}

const int N = 50005;

int n;

BigInt f[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    f[0] = 0, f[1] = 1, f[2] = 1, f[3] = 4, f[4] = 3;
    for (int i = 5; i <= n; ++i) f[i] = 3 * f[i - 2] - f[i - 4];
    std::cout << (n & 1 ? 1 : 5) * (f[n] * f[n]) << std::endl;
    return 0;
}