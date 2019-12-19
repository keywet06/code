#include <bits/stdc++.h>
const int N = 8000005;
const int M = 8388608;
const int l13 = (1 << 13) - 1;
char t;
int n, q, l, r, ans, x, y;
unsigned short int sum[N * 2];
unsigned short int uncamult(unsigned int, unsigned int);
void update(int);
void build(int, int, int);
inline unsigned short int uncamult(unsigned int x, unsigned int y) {
    static unsigned int ans, i;
    ans = 0;
    i = 0;
    while (x) {
        if (x & 1) {
            ans ^= y << i;
        }
        x >>= 1;
        ++i;
    }
    return (ans ^ (ans >> 13)) & l13;
}
inline void update(int v) {
    sum[v] = uncamult(sum[v << 1], sum[v << 1 | 1]);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> q >> t;
    while (t == '\n' || t == ' ' || t == '\r') {
        std::cin >> t;
    }
    for (int i = 1; i < n; ++i) {
        sum[i + M] = 1 ^ (1 << (t < 'a' ? t - '0' : t - 'a' + 10));
        std::cin >> t;
    }
    sum[n + M] = 1 ^ (1 << (t < 'a' ? t - '0' : t - 'a' + 10));
    for (int i = N - 1; i; --i) {
        update(i);
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> l >> r;
        ans = 1;
        x = l;
        y = r;
        for (l += (M - 1), r += (M + 1); l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (!(l & 1)) {
                ans = uncamult(ans, sum[l ^ 1]);
            }
            if (r & 1) {
                ans = uncamult(ans, sum[r ^ 1]);
            }
        }
        l = x;
        r = y;
        for (int i = 0; i < 13; ++i) {
            std::cout << (ans >> i & 1);
        }
        std::cout << std::endl;
        sum[x += M] ^= 1;
        sum[x] <<= 1;
        sum[x] |= sum[x] >> 13 << 1;
        sum[x] ^= 1;
        sum[x] &= l13;
        for (x >>= 1; x; x >>= 1) {
            update(x);
        }
        sum[y += M] ^= 1;
        sum[y] <<= 1;
        sum[y] |= sum[y] >> 13 << 1;
        sum[y] ^= 1;
        sum[y] &= l13;
        for (y >>= 1; y; y >>= 1) {
            update(y);
        }
    }
    return 0;
}