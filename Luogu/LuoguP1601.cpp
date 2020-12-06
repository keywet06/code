#define OCT_CODE_REQUIRES
#define LUOGU
#ifdef OCT_CODE_REQUIRES

// oct code require pre-document.cpp
// oct code object pre-document
#ifndef OCT_CODE_OBJECT_PREx2dDOCUMENT
#define OCT_CODE_OBJECT_PREx2dDOCUMENT

#if defined(ONLINE_JUDGE) && !defined(LUOGU)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,tune=native")
#endif

// oct code object stl/bits/stdc++.h
#ifndef OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#define OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#include <bits/stdc++.h>
#endif  // oct code end stl/bits/stdc++.h

#define debug std::cerr << "Debug(" << __LINE__ << "): "
#ifdef ONLINE_JUDGE
#define cerr cout
#endif
#define pub push_back
#define pob pop_back
#define pup push
#define mkp make_pair
#define fir first
#define sec second
#define ite iterator
#define lob lower_bound
#define upb upper_bound
#define reg register

using uint8 = unsigned char;
using uint16 = unsigned short size_t;
using uint32 = unsigned size_t;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short size_t;
using int32 = size_t;
using int64 = long long;
using ldb = long double;
using pi5 = std::pair<int32, int32>;
using pi6 = std::pair<int64, int64>;
using pi56 = std::pair<int32, int64>;
using pi65 = std::pair<int64, int32>;

namespace oct {

template <typename _Tp>
class priority_queue
    : public std::priority_queue<_Tp, std::vector<_Tp>, std::greater<_Tp> > {};

/* Array tn4 is the 4-direction changes in coordinate system.
 * The directions in order is {rght, up, left, down}.
 */
const size_t tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const size_t tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                       {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const double exp = 1e-8;

void sync(size_t pre = 8);
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);
template <typename _Tp>
bool in(_Tp x, _Tp l, _Tp r);
template <typename _Tp>
bool in(_Tp x, _Tp y, _Tp l, _Tp r);
template <typename _Tp>
_Tp sqr(_Tp x);
template <typename _Tp>
_Tp power(_Tp x, int64 tm);
template <typename _Tp>
void sort(_Tp &x, _Tp &y);
template <typename _Tp1, typename _Tp2>
std::pair<_Tp1, _Tp2> operator+(std::pair<_Tp1, _Tp2> x,
                                std::pair<_Tp1, _Tp2> y);
template <typename _Tp>
_Tp &operator+=(_Tp &x, _Tp y);
template <typename _Tp>
_Tp gcd(_Tp &x, _Tp &y);

inline void sync(size_t pre) {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout.flags(std::ios::fixed);
    std::cout.precision(pre);
    std::cout.setf(std::ios::showpoint);
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
inline bool in(_Tp x, _Tp y, _Tp l, _Tp r) {
    return l <= x && y <= r;
}
template <typename _Tp>
inline _Tp sqr(_Tp x) {
    return x * x;
}
template <typename _Tp>
inline _Tp power(_Tp x, int64 tm) {
    return tm == 1 ? x
                   : (tm & 1 ? power(x * x, tm / 2) * x : power(x * x, tm / 2));
}
template <typename _Tp>
inline void sort(_Tp &x, _Tp &y) {
    if (x > y) std::swap(x, y);
}
template <typename _Tp1, typename _Tp2>
inline std::pair<_Tp1, _Tp2> operator+(std::pair<_Tp1, _Tp2> x,
                                       std::pair<_Tp1, _Tp2> y) {
    return x.fir += y.fir, x.sec += y.sec, x;
}
template <typename _Tp>
inline _Tp &operator+=(_Tp &x, _Tp y) {
    return x = x + y;
}
template <typename _Tp>
inline _Tp gcd(_Tp &x, _Tp &y) {
    return std::__gcd(x, y);
}

}  // namespace oct

#endif  // oct code end pre-document

// oct code require needcpp11.cpp
// oct code object needcpp11.cpp
#ifndef OCT_CODE_OBJECT_NEEDCPP11x2eCPP
#define OCT_CODE_OBJECT_NEEDCPP11x2eCPP

#if __cplusplus < 201103L
#error "This program or object needs C++11 or higher standard"
#endif

#endif  // oct code end needcpp11.cpp

// oct code require ubint.cpp
// oct code object ubint.cpp
#ifndef OCT_CODE_OBJECT_UBINTx2eCPP
#define OCT_CODE_OBJECT_UBINTx2eCPP

namespace oct {

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
class ubint {
   protected:
    _Vec vec;

   public:
    ubint() {}
    ubint(_Tp x) {
        if (!x) vec.pub(0);
        while (x) vec.pub(x % _Base), x /= _Base;
    }
    ubint(std::string s) {
        for (size_t i = 0; i < s.size(); ++i) vec.pub(s[i] - '0');
    }
    ~ubint() {}
    size_t size() { return vec.size(); }
    void resize(size_t new_size) { vec.resize(new_size); }
    void pop() { vec.pob(); }
    _Tp &operator[](size_t x) { return vec[x]; }
    void update() {
        std::cout << "UPDATE" << std::endl;
        for (size_t i = 0; i + 1 < size(); ++i) {
            std::cout << i << ' ' << size() << std::endl;
            vec[i + 1] += vec[i] / _Base, vec[i] %= _Base;
        }
        std::cout << "PAUSE" << std::endl;
        while (vec[size() - 1] >= _Base) {
            vec.pub(vec[size() - 1] / _Base), vec[size() - 2] %= _Base;
        }
        std::cout << "NICE" << std::endl;
    }
};

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> operator+(ubint<_Tp, _Base, _Vec> x,
                                  ubint<_Tp, _Base, _Vec> y) {
    if (x.size() < y.size()) std::swap(x, y);
    ubint<_Tp, _Base, _Vec> ret(x);
    for (size_t i = 0; i < y.size(); ++i) ret[i] += y[i];
    return ret.update(), ret;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> operator+(ubint<_Tp, _Base, _Vec> x, _Tp y) {
    return x + ubint<_Tp, _Base, _Vec>(y);
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> operator+(_Tp x, ubint<_Tp, _Base, _Vec> y) {
    return ubint<_Tp, _Base, _Vec>(x) + y;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> &operator+=(ubint<_Tp, _Base, _Vec> &x,
                                    ubint<_Tp, _Base, _Vec> y) {
    return x = x + y;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> &operator+=(ubint<_Tp, _Base, _Vec> &x, _Tp y) {
    return x = x + y;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> operator-(ubint<_Tp, _Base, _Vec> x,
                                  ubint<_Tp, _Base, _Vec> y) {
    ubint<_Tp, _Base, _Vec> ret(x);
    for (size_t i = 0; i < y.size(); ++i) {
        ret[i] = (ret[i] -= y[i]) < 0 ? ret[i] : (--ret[i + 1], ret[i] + _Base);
    }
    size_t i = y.size();
    while (ret[i] < 0) ret[i] += _Base, --ret[++i];
    while (!ret[ret.size() - 1]) ret.pop();
    return ret;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> operator-(ubint<_Tp, _Base, _Vec> x, _Tp y) {
    return x - ubint<_Tp, _Base, _Vec>(y);
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> operator-(_Tp x, ubint<_Tp, _Base, _Vec> y) {
    return ubint<_Tp, _Base, _Vec>(x) - y;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> &operator-=(ubint<_Tp, _Base, _Vec> &x,
                                    ubint<_Tp, _Base, _Vec> y) {
    return x = x - y;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
ubint<_Tp, _Base, _Vec> &operator-=(ubint<_Tp, _Base, _Vec> &x, _Tp y) {
    return x = x - y;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
std::istream &operator>>(std::istream &in, ubint<_Tp, _Base, _Vec> x) {
    std::string s;
    return in >> s, x = s, in;
}

template <typename _Tp, _Tp _Base, typename _Vec = std::vector<_Tp> >
std::ostream &operator<<(std::ostream &out, ubint<_Tp, _Base, _Vec> x) {
    for (size_t i = x.size() - 1; ~i; --i) out << x[i];
    return out;
}

}  // namespace oct

#endif

#endif

using bigint = oct::ubint<size_t, 10>;

bigint a, b;

size_t main() {
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    return 0;
}