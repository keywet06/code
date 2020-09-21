#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define debug std::cerr << "Debug(" << __LINE__ << "): "
#define pub push_back
#define pob pop_back
#define pup push
#define mkp make_pair
#define fir first
#define sec second
#define ite iterator
#define lob lower_bound
#define upb upper_bound

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using dr = double;
using pi32 = std::pair<int32, int32>;
using pi32pi32 = std::pair<int32, pi32>;
using cpdr = std::complex<dr>;
using vi32 = std::vector<int32>;
using qi32 = std::queue<int32>;
using spi32 = std::set<pi32>;
using spi32it = spi32::iterator;

namespace oct {

/* Array tn4 is the 4-direction changes in coordinate system.
 * The directions in order is {right, up, left, down}.
 */
const int tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                       {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

void sync();
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);
template <typename _Tp>
bool in(_Tp x, _Tp l, _Tp r);
template <typename _Tp>
_Tp sqr(_Tp x);
template <typename _Tp>
_Tp power(_Tp x, int m);

inline void sync() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}
template <typename _Tp>
inline _Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}
template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}
template <typename _Tp>
inline bool in(_Tp x, _Tp l, _Tp r) {
    return l <= x && x <= r;
}
template <typename _Tp>
inline _Tp sqr(_Tp x) {
    return x * x;
}
template <typename _Tp>
inline _Tp power(_Tp x, int m) {
    return m == 1 ? x : (m & 1 ? power(x * x, m / 2) * x : power(x * x, m / 2));
}

}  // namespace oct

// the pre-document end

const int N = 3000005;
const double pi = acos(-1);

void change(cpdr *f, int n);
void fft(cpdr *f, int n, int rev);
void fastwrite(int x);

char ch[N], d[N];
int n, k, x, y = 100, cnt;
int rev[N];
cpdr a[N], b[N];

inline void change(cpdr *f, int n) {
    for (int i = 0; i < n; ++i) {
        rev[i] = rev[i >> 1] >> 1 | (i & 1 ? n : 0) >> 1;
    }
    for (int i = 0; i < n; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
}
inline void fft(cpdr *f, int n, int rev) {
    register cpdr step, cur, g, h;
    register int l, b, k, i;
    change(f, n);
    for (l = 2; l <= n; l <<= 1) {
        step = cpdr(cos(2 * pi / l), sin(2 * pi * rev / l));
        for (b = 0; b < n; b += l) {
            cur = cpdr(1, 0);
            for (k = b; k < b + (l >> 1); ++k) {
                g = f[k], h = f[k + (l >> 1)] * cur;
                f[k] = g + h;
                f[k + (l >> 1)] = g - h;
                cur *= step;
            }
        }
    }
    if (!~rev) for (i = 0; i < n; ++i) f[i] /= n;
}
inline void fastwrite(int x) {
    while (x) {
        d[--y] = x % 10 + '0';
        x /= 10;
    }
    for (; y < 100; ++y) ch[cnt++] = d[y]; 
    if (cnt > 1000000) ch[cnt] = 0, printf("%s", ch), cnt = 0;
}

int main() {
    srand(time(NULL));
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) /* std::cin >> x, */a[rand() % 1000 + 1].real(1);
    b[0].real(1);
    fft(a, 1 << 20, 1);
    fft(b, 1 << 20, 1);
    for (int i = 0; i < 1 << 20; ++i) a[i] = oct::power(a[i], k) * b[i];
    fft(a, 1 << 20, -1);
    // if (n == 1000) return 0;
    for (int i = 0; i < 1 << 20; ++i) {
        if (int64(a[i].real() + 0.5)) fastwrite(i), ch[cnt++] = ' ';
    }
    ch[cnt++] = '\n';
    printf("%s", ch);
    return 0;
}