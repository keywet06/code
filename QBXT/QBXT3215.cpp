#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;
using ldou = long double;

inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }

inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

const ldou PI = acosl(-1);

using Virt = std::complex<ldou>;

inline std::vector<Virt> FFT(std::vector<Virt> f, bool Flag) {
    const int N = 1 << 23;
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
        if ((x = Base.Rev[i] >> Shift) > i) std::swap(f[x], f[i]);
    }
    for (int i = 1; i < n; i <<= 1) {
        Virt wn(cosl(PI / i), sinl(PI / i));
        for (int j = 0; j < n; j += i << 1) {
            Virt w(1, 0);
            for (int k = 0; k < i; ++k) {
                Virt x = f[j | k], y = w * f[j | i | k];
                f[j | k] = x + y, f[j | i | k] = x - y, w *= wn;
            }
        }
    }
    if (Flag) {
        std::reverse(f.begin() + 1, f.end());
        for (Virt &u : f) u /= n;
    }
    return f;
}

inline std::vector<Virt> FFT(std::vector<Virt> f) { return FFT(f, false); }
inline std::vector<Virt> IFFT(std::vector<Virt> f) { return FFT(f, true); }

inline std::vector<Virt> Mul(std::vector<Virt> A, std::vector<Virt> B) {
    int d = A.size() + B.size() - 1, r = BiBlm(d);
    A.resize(r), B.resize(r), A = FFT(A), B = FFT(B);
    for (int i = 0; i < r; ++i) A[i] *= B[i];
    A = IFFT(A), A.resize(d);
    return A;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(3);
    int n, m, r;
    std::cin >> n >> m >> r;
    int l = (r + 1) / 2, e = m + 2 * l;
    std::vector<Virt> a(n * e);
    for (int i = 0; i < n; ++i) {
        for (int j = 0, x; j < m; ++j) std::cin >> x, a[i * e + j + l] = x;
    }
    std::vector<Virt> k((r * 2 + 1) * e);
    for (int i = -r; i <= r; ++i) {
        for (int j = -r; j <= r; ++j) {
            if (i * i + j * j >= r * r) continue;
            k[(r + i) * e + (r + j)] = 1 / (sqrtl(i * i + j * j) + 1);
        }
    }
    a = Mul(a, k);
    int p = r * e + r + l;
    ldou Ans = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            Ans = std::max(Ans, a[i * e + j + p].real());
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}