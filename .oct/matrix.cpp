// oct code object matrix.cpp
#ifndef OCT_CODE_OBJECT_MATRIXx2eCPP
#define OCT_CODE_OBJECT_MATRIXx2eCPP

// oct code object stl/bits/stdc++.h
#ifndef OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#define OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#include <bits/stdc++.h>
#endif  // oct code end stl/bits/stdc++.h

namespace oct {

template <typename _Tp, size_t _N, size_t _M>
class matrix {
   protected:
    _Tp data[_N][_M];

   public:
    matrix();
    matrix(const _Tp _data[_N][_M]);
    _Tp *operator[](const size_t i);
};

template <typename _Tp, size_t _N, size_t _M>
matrix<_Tp, _N, _M> operator+(const matrix<_Tp, _N, _M> x,
                              const matrix<_Tp, _N, _M> y);
template <typename _Tp, size_t _N, size_t _K, size_t _M>
matrix<_Tp, _N, _M> operator*(const matrix<_Tp, _N, _K> x,
                              const matrix<_Tp, _K, _M> y);
template <typename _Tp, size_t _N, size_t _M>
matrix<_Tp, _N, _M> &operator+=(matrix<_Tp, _N, _M> &x,
                                const matrix<_Tp, _N, _M> y);
template <typename _Tp, size_t _N, size_t _K, size_t _M>
matrix<_Tp, _N, _M> &operator*=(matrix<_Tp, _N, _K> &x,
                                const matrix<_Tp, _K, _M> y);

template <typename _Tp, size_t _N, size_t _M>
inline matrix<_Tp, _N, _M>::matrix() {
    memset(data, 0, sizeof(data));
}
template <typename _Tp, size_t _N, size_t _M>
inline matrix<_Tp, _N, _M>::matrix(const _Tp _data[_N][_M]) {
    memcpy(data[i], _data[i], sizeof(data));
}
template <typename _Tp, size_t _N, size_t _M>
inline _Tp *matrix<_Tp, _N, _M>::operator[](const size_t i) {
    return data[i];
}
template <typename _Tp, size_t _N, size_t _M>
inline matrix<_Tp, _N, _M> operator+(const matrix<_Tp, _N, _M> x,
                                     const matrix<_Tp, _N, _M> y) {
    matrix<_Tp, _N, _M> ret;
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _M; ++j) ret[i][j] = x[i][j] + y[i][j];
    }
}
template <typename _Tp, size_t _N, size_t _K, size_t _M>
inline matrix<_Tp, _N, _M> operator*(const matrix<_Tp, _N, _K> x,
                                     const matrix<_Tp, _K, _M> y) {
    matrix<_Tp, _N, _M> ret;
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _M; ++j) {
            for (int k = 0; k < _K; ++k) {
                ret[i][j] = ret[i][j] + x[i][k] * y[k][j];
            }
        }
    }
    return ret;
}
template <typename _Tp, size_t _N, size_t _M>
inline matrix<_Tp, _N, _M> &operator+=(matrix<_Tp, _N, _M> &x,
                                       const matrix<_Tp, _N, _M> y) {
    return x = x + y;
}
template <typename _Tp, size_t _N, size_t _K, size_t _M>
inline matrix<_Tp, _N, _M> &operator*=(matrix<_Tp, _N, _K> &x,
                                       const matrix<_Tp, _K, _M> y) {
    return x = x * y;
}

}  // namespace oct

#endif  // oct code object matrix.cpp