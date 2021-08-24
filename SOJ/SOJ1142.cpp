// oct code object gmatrix.cpp
#ifndef OCT_CODE_OBJECT_GMATRIXx2eCPP
#define OCT_CODE_OBJECT_GMATRIXx2eCPP

// oct code object stl/bits/stdc++.h
#ifndef OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#define OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#include <bits/stdc++.h>
#endif  // oct code end stl/bits/stdc++.h

namespace oct {

template <typename _Tp, size_t _N, size_t _M>
class gmatrix {
   protected:
    _Tp data[_N][_M];

   public:
    gmatrix();
    gmatrix(const _Tp _data[_N][_M]);
    _Tp *operator[](const size_t i);
};

template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> operator+(gmatrix<_Tp, _N, _M> x, gmatrix<_Tp, _N, _M> y);
template <typename _Tp, size_t _N, size_t _K, size_t _M>
gmatrix<_Tp, _N, _M> operator*(gmatrix<_Tp, _N, _K> x, gmatrix<_Tp, _K, _M> y);
template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> &operator+=(gmatrix<_Tp, _N, _M> &x,
                                 gmatrix<_Tp, _N, _M> y);
template <typename _Tp, size_t _N, size_t _K, size_t _M>
gmatrix<_Tp, _N, _M> &operator*=(gmatrix<_Tp, _N, _K> &x,
                                 gmatrix<_Tp, _K, _M> y);

template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M>::gmatrix() {
    memset(data, 0, sizeof(data));
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M>::gmatrix(const _Tp _data[_N][_M]) {
    memcpy(data, _data, sizeof(data));
}
template <typename _Tp, size_t _N, size_t _M>
inline _Tp *gmatrix<_Tp, _N, _M>::operator[](size_t i) {
    return data[i];
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M> operator+(gmatrix<_Tp, _N, _M> x,
                                      gmatrix<_Tp, _N, _M> y) {
    gmatrix<_Tp, _N, _M> ret;
    for (size_t i = 0; i < _N; ++i) {
        for (size_t j = 0; j < _M; ++j) ret[i][j] = x[i][j] + y[i][j];
    }
    return ret;
}
template <typename _Tp, size_t _N, size_t _K, size_t _M>
inline gmatrix<_Tp, _N, _M> operator*(gmatrix<_Tp, _N, _K> x,
                                      gmatrix<_Tp, _K, _M> y) {
    gmatrix<_Tp, _N, _M> ret;
    for (size_t i = 0; i < _N; ++i) {
        for (size_t j = 0; j < _M; ++j) {
            for (size_t k = 0; k < _K; ++k) {
                ret[i][j] = std::max(ret[i][j], x[i][k] + y[k][j]);
            }
        }
    }
    return ret;
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M> &operator+=(gmatrix<_Tp, _N, _M> &x,
                                        gmatrix<_Tp, _N, _M> y) {
    return x = x + y;
}
template <typename _Tp, size_t _N, size_t _K, size_t _M>
inline gmatrix<_Tp, _N, _M> &operator*=(gmatrix<_Tp, _N, _K> &x,
                                        gmatrix<_Tp, _K, _M> y) {
    return x = x * y;
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M> &operator%=(gmatrix<_Tp, _N, _M> &x, const _Tp y) {
    for (size_t i = 0; i < _N; ++i) {
        for (size_t j = 0; j < _M; ++j) x[i][j] %= y;
    }
    return x;
}

}  // namespace oct

#endif  // oct code object gmatrix.cpp

using int64 = long long;
using lmt = oct::gmatrix<int64, 2, 1>;
using tmt = oct::gmatrix<int64, 2, 2>;

const int N = 100005;
const int64 P = 998244353;

int n;

lmt t;

tmt sum, ans;
tmt a[N];

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i][1][1];
    ans += sum = a[n];
    for (int i = n - 1; i; --i) ans += (sum = a[i] * sum + a[i]) %= P;
    std::cout << (t = ans * t)[1][0] << std::endl;
    return 0;
}