#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;
using ldou = long double;

inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

using virt = std::complex<ldou>;

const ldou PI = acos(-1);

inline std::vector<virt> FFT(std::vector<virt> f, bool Flag) {
    const int N = 1 << 20;
    static struct FFTBase {
        std::vector<int> Rev;
        FFTBase(int n) : Rev(n) {
            int c = BiCtz(n) - 1;
            for (int i = 1; i < n; ++i) {
                Rev[i] = Rev[i >> 1] >> 1 | (i & 1) << c;
            }
        }
    } Base(N);
    int n = BiBlm(f.size()), Shift = BiCtz(N) - BiCtz(n);
    f.resize(n);
    for (int i = 1, x; i < n; ++i) {
        if ((x = Base.Rev[i] >> Shift) > i) std::swap(f[i], f[x]);
    }
    for (int i = 1; i < n; i <<= 1) {
        virt wn(cosl(PI / i), sinl(PI / i));
        for (int j = 0; j < n; j += i << 1) {
            virt w(1, 0);
            for (int k = 0; k < i; ++k) {
                virt x = f[j | k], y = w * f[j | i | k];
                f[j | k] = x + y, f[j | i | k] = x - y, w *= wn;
            }
        }
    }
    if (Flag) {
        std::reverse(f.begin() + 1, f.end());
        for (virt &u : f) u /= n;
    }
    return f;
}

inline std::vector<virt> FFT(std::vector<virt> f) { return FFT(f, false); }
inline std::vector<virt> IFFT(std::vector<virt> f) { return FFT(f, true); }

inline std::vector<int64> Sqr(std::vector<int64> f) {
    int d = f.size() + f.size() - 1, r = BiBlm(d);
    std::vector<virt> A(r);
    for (int i = 0; i < f.size(); ++i) A[i] = f[i];
    A = FFT(A);
    for (virt &u : A) u = u * u;
    A = IFFT(A);
    std::vector<int64> Ret(d);
    for (int i = 0; i < d; ++i) Ret[i] = int64(A[i].real() + 0.5);
    return Ret;
}

inline int64 C2(int64 x) { return x * (x - 1) / 2; }
inline int64 C3(int64 x) { return x * (x - 1) * (x - 2) / 6; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    const int N = 100000;
    std::vector<int64> a(N + 1);
    for (int i = 0, x; i < n; ++i) std::cin >> x, ++a[x];
    std::vector<int64> b(Sqr(a));
    for (int i = 1; i <= N; ++i) b[i << 1] -= a[i];
    for (int64 &u : b) u /= 2;
    for (int i = 1; i <= N << 1; ++i) b[i] += b[i - 1];
    int64 Ans = 0, Sum = 0;
    for (int i = 1; i <= N; ++i) {
        Ans += a[i] * (C2(Sum) - b[i]) + C2(a[i]) * Sum + C3(a[i]), Sum += a[i];
    }
    std::cout << std::fixed << std::setprecision(7);
    std::cout << ldou(Ans) / C3(n) << std::endl;
    return 0;
}