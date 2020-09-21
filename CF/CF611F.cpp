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
using pi32 = std::pair<int32, int32>;
using vi32 = std::vector<int32>;
using qi32 = std::queue<int32>;
using spi32 = std::set<pi32>;

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

}  // namespace oct

// the pre-document end

const int N = 500005;
const int M = 1000005;
const int mod = 100000007;

struct node {
    int64 num;
    int type;
    node() {}
    node(int _type, int64 _num) { num = _num, type = _type; }
};

char op[N];
int n, r, c, minx, miny, maxx, maxy, nowx, nowy;
std::vector<node> v1, v2, v11, v22;

void changes(char c, int &x, int &y) {
    if (c == 'R') --y;
    if (c == 'L') ++y;
    if (c == 'D') --x;
    if (c == 'U') ++x;
}
int gett(char c) { return c != 'R' && c != 'L'; }

int main() {
    std::cin >> n >> c >> r;
    std::cin >> op;
    v1.clear(), v11.clear(), v2.clear(), v22.clear();
    minx = miny = maxx = maxy = nowx = nowy = 0;
    for (int i = 0; i < n; ++i) {
        changes(op[i], nowx, nowy);
        int type = gett(op[i]);
        if (type == 0) {
            if (maxy < nowy) {
                maxy = nowy;
                v1.push_back(node(type, i + 1));
            } else if (miny > nowy) {
                miny = nowy;
                v1.push_back(node(type, i + 1));
            }
        } else {
            if (maxx < nowx) {
                maxx = nowx;
                v2.push_back(node(type, i + 1));
            } else if (minx > nowx) {
                minx = nowx;
                v2.push_back(node(type, i + 1));
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        changes(op[i], nowx, nowy);
        int type = gett(op[i]);
        if (type == 0) {
            if (maxy < nowy) {
                maxy = nowy;
                v11.push_back(node(type, i + 1 + n));
            } else if (miny > nowy) {
                miny = nowy;
                v11.push_back(node(type, i + 1 + n));
            }
        } else {
            if (maxx < nowx) {
                maxx = nowx;
                v22.push_back(node(type, i + 1 + n));
            } else if (minx > nowx) {
                minx = nowx;
                v22.push_back(node(type, i + 1 + n));
            }
        }
    }
    if (v11.size()) {
        while (v1.size() < c) {
            for (int j = 0; j < v11.size(); ++j) {
                v1.push_back(v11[j]);
                v11[j].num += n;
                if (v1.size() >= c) break;
            }
        }
    }
    if (v22.size()) {
        while (v2.size() < r) {
            for (int j = 0; j < v22.size(); ++j) {
                v2.push_back(v22[j]);
                v22[j].num += n;
                if (v2.size() >= r) break;
            }
        }
    }
    int64 ans = 0;
    int f1 = 0, f2 = 0;
    while (f1 < v1.size() || f2 < v2.size()) {
        if (f2 == v2.size() || f1 < v1.size() && v1[f1].num < v2[f2].num) {
            ans = (ans + v1[f1++].num * r % mod) % mod;
            c--;
        } else {
            ans = (ans + v2[f2++].num * c % mod) % mod;
            r--;
        }
        if (r <= 0 || c <= 0) break;
    }
    std::cout << (r && c ? -1 : ans) << std::endl;
    return 0;
}