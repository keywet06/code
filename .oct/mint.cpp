// oct code object mint.cpp
#ifndef OCT_CODE_OBJECT_MINTx2eCPP
#define OCT_CODE_OBJECT_MINTx2eCPP

namespace oct {

template <typename _Tp, _Tp mod>
class mint {
   public:
    _Tp x;
    inline mint() { x = 0; }
    inline mint(_Tp _x) { x = _x; }
    inline _Tp &num() { return x; }
    inline _Tp &data() { return x; }
};

template <typename _Tp, _Tp mod>
inline mint<_Tp, mod> operator+(mint<_Tp, mod> x, mint<_Tp, mod> y) {
    return (x.num() + y.num()) % mod;
}
template <typename _Tp, _Tp mod>
inline mint<_Tp, mod> &operator+=(mint<_Tp, mod> &x, mint<_Tp, mod> y) {
    return x = x + y;
}
template <typename _Tp, _Tp mod>
inline mint<_Tp, mod> operator-(mint<_Tp, mod> x, mint<_Tp, mod> y) {
    return (x.num() + mod - y.num()) % mod;
}
template <typename _Tp, _Tp mod>
inline mint<_Tp, mod> &operator-=(mint<_Tp, mod> &x, mint<_Tp, mod> y) {
    return x = x - y;
}
template <typename _Tp, _Tp mod>
inline mint<_Tp, mod> operator*(mint<_Tp, mod> x, mint<_Tp, mod> y) {
    return x.num() * y.num() % mod;
}
template <typename _Tp, _Tp mod>
inline mint<_Tp, mod> &operator*=(mint<_Tp, mod> &x, mint<_Tp, mod> y) {
    return x = x * y;
}
#ifdef STL_BITS__2F_STDCx2Bx2Bx2FH
template <typename _Tp, _Tp mod>
inline std::istream &operator>>(std::istream &in, mint<_Tp, mod> x) {
    return in >> x.num();
}
template <typename _Tp, _Tp mod>
inline std::ostream &operator>>(std::ostream &out, mint<_Tp, mod> x) {
    return out << x.num();
}
#endif

}  // namespace oct

#endif  // oct code end mint.cpp