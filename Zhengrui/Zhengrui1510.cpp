#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>

const int MAXN = 33333;
typedef unsigned long long LL;
int A[3][2];
LL f[3][MAXN][2];
const int MAXL = 66666;
int lhs[2][MAXL], rhs[2][MAXL];

typedef long long orill;
struct FFT {
    static const int mod = 998244353;
    int mul(int a, int b) { return (orill)a * b % mod; }
    void reduce(int& x) { x += x >> 31 & mod; }
    int pow(int a, int b, int r = 1) {
        for (; b; b >>= 1, a = mul(a, a)) {
            if (b & 1) r = mul(r, a);
        }
        return r;
    }
    void fma(int& x, int y, int z) { x = ((orill)y * z + x) % mod; }
    int lim, dig, rev[MAXL], wn[MAXL];
    void initall(int sz) {
        for (int mid = 1; mid < sz; mid <<= 1) {
            const int Wn = pow(3, (mod - 1) / mid / 2);
            for (int i = 0, W = 1; i != mid; ++i) {
                wn[mid + i] = W, W = mul(W, Wn);
            }
        }
    }
    void init(int sz) {
        lim = 1, dig = -1;
        while (lim < sz) lim <<= 1, ++dig;
        for (int i = 1; i != lim; ++i) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << dig;
        }
    }
    void NTT(int* A, int typ) {
        for (int i = 0; i < lim; ++i)
            if (i < rev[i]) std::swap(A[i], A[rev[i]]);
        for (int mid = 1; mid != lim; mid <<= 1) {
            for (int k = 0; k != lim; k += mid << 1) {
                for (int l = 0; l != mid; ++l) {
                    const int Y = mul(A[l + k + mid], wn[mid + l]);
                    reduce(A[l + k + mid] = A[l + k] - Y);
                    reduce(A[l + k] += Y - mod);
                }
            }
        }
        if (typ == -1) {
            const int liminv = pow(lim, mod - 2);
            for (int i = 0; i != lim; ++i) A[i] = mul(A[i], liminv);
            std::reverse(A + 1, A + lim);
        }
    }
} fft;
int main() {
    int lim = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            std::cin >> A[j][i];
            lim = std::max(lim, A[j][i]);
        }
    fft.init(lim * 2 + 1);
    fft.initall(fft.lim);
    LL ans = 0;
    for (int dig = 0; lim >> dig; ++dig) {
        memset(f, 0, sizeof f);
        for (int i = 0; i < 3; ++i) {
            static int tmp[2][MAXL];
            memset(lhs, 0, sizeof lhs);
            memset(rhs, 0, sizeof rhs);
            memset(tmp, 0, sizeof tmp);
            for (int j = 0; j <= A[i][0]; ++j) lhs[j >> dig & 1][j] = 1;
            for (int j = 0; j <= A[i][1]; ++j) rhs[j >> dig & 1][lim - j] = 1;
            fft.NTT(lhs[0], 1);
            fft.NTT(lhs[1], 1);
            fft.NTT(rhs[0], 1);
            fft.NTT(rhs[1], 1);
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < fft.lim; ++l) {
                        fft.fma(tmp[j ^ k][l], lhs[j][l], rhs[k][l]);
                    }
                }
            }
            for (int j = 0; j < 2; ++j) {
                fft.NTT(tmp[j], -1);
                for (int k = 0; k <= lim; ++k) {
                    f[i][k][j] = tmp[j][lim - k] + (k ? tmp[j][lim + k] : 0);
                }
            }
        }
        static LL sl[2], sr[2], tmp[2];
        for (int i = 1; i < 3; ++i) {
            memset(sl, 0, sizeof sl);
            memset(sr, 0, sizeof sr);
            for (int j = 0; j <= lim; ++j) {
                memset(tmp, 0, sizeof tmp);
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        tmp[k ^ l] += sl[k] * f[i][j][l] + sr[k] * f[0][j][l] +
                                      f[i][j][k] * f[0][j][l];
                    }
                }
                for (int k = 0; k < 2; ++k) {
                    sl[k] += f[0][j][k], sr[k] += f[i][j][k];
                }
                for (int k = 0; k < 2; ++k) f[0][j][k] = tmp[k];
            }
        }
        for (int i = 0; i <= lim; ++i) {
            for (int j = 0; j < 2; ++j) {
                ans += f[0][i][j] * (((i >> dig & 1) ^ j) << dig);
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}