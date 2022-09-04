#include <bits/stdc++.h>

using uint64 = unsigned long long;

const int Ic = sizeof(uint64) << 3;
const int Ice = __builtin_ctz(Ic);
const int Icd = Ic - 1;

const int MP = 1000000007;

const int N = 240;
const int L = 200;
const int R = 40;
const int M = 10000000;
const int Ms = 60000;
const int K = 3000000;
const int Ks = 150000;

const int LA = MP / sizeof(uint64) + 1;

const char *s = "0123456789ABCDEF";

using BS = std::bitset<N>;

uint64 BIT[LA];

int p, q;
int a[N];

int ni[M], nj[K], pi[M];
BS bi[M], bj[K];

inline void Solve(int l, int r, int n, int s, int *c, BS *b) {
    b[0][l] = 1, c[0] = a[l++];
    int T = 1;
    while (T < n) {
        int cT = T, us = std::min(s, cT), t = cT / us;
        for (int i = 0; i < cT; i += t) {
            if (T >= n) break;
            b[T] = b[i], b[T][l] = 1, c[T] = (c[i] + a[l]) % p, ++T;
        }
        ++l;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> p >> q;
    for (int i = 0; i < N; ++i) std::cin >> a[i];
    Solve(0, L, M, Ms, ni, bi);
    Solve(L, N, K, Ks, nj, bj);
    for (int i = 0; i < M; ++i) pi[i] = i, BIT[ni[i] >> Ice] |= 1 << (ni[i] & Icd);
    std::sort(pi, pi + M, [](int x, int y) { return ni[x] < ni[y]; });
    while (q--) {
        int i, x, c;
        std::cin >> x;
        for (i = 0; i < K; ++i) {
            c = x - nj[i];
            if (c < 0) c += p;
            if ((BIT[c >> Ice] >> (c & Icd)) & 1) break;
        }
        int l = 0, r = M - 1, Mid;
        while (l < r) Mid = l + r >> 1, ni[pi[Mid]] < c ? (l = Mid + 1) : (r = Mid);
        // std::cout << ddd << " | " << i << '\n';
        // std::cout << ni[ddd] << " + " << nj[i] << '\n';
        BS Ans = bi[pi[l]] | bj[i];
        // for (int i = 0; i < N; ++i) if (Ans[i]) std::cout << a[i] << ' ';
        // std::cout << '\n';
        for (int i = N; i; i -= 4) std::cout << s[Ans[i - 1] << 3 | Ans[i - 2] << 2 | Ans[i - 3] << 1 | Ans[i - 4]];
        std::cout << '\n';
    }
    return 0;
}