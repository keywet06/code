namespace oct {

template <typename _Tp, int mod>
class mod_int {
   public:
    _Tp x;
    inline mod_int() { x = 0; }
    inline mod_int(_Tp _x) { x = _x; }
    inline _Tp &num() { return x; }
};

template <typename _Tp, int mod>
inline mod_int<_Tp, mod> operator+(mod_int<_Tp, mod> x, mod_int<_Tp, mod> y) {
    return (x.x + y.x) % mod;
}
template <typename _Tp, int mod>
inline mod_int<_Tp, mod> &operator+=(mod_int<_Tp, mod> &x,
                                     mod_int<_Tp, mod> y) {
    return x.x = (x.x + y.x) % mod, x;
}
template <typename _Tp, int mod>
inline mod_int<_Tp, mod> operator-(mod_int<_Tp, mod> x, mod_int<_Tp, mod> y) {
    return (x.x + mod - y.x) % mod;
}
template <typename _Tp, int mod>
inline mod_int<_Tp, mod> &operator-=(mod_int<_Tp, mod> &x,
                                     mod_int<_Tp, mod> y) {
    return x.x = (x.x + mod - y.x) % mod, x;
}
template <typename _Tp, int mod>
inline mod_int<_Tp, mod> operator*(mod_int<_Tp, mod> x, mod_int<_Tp, mod> y) {
    return (x.x * y.x) % mod;
}
template <typename _Tp, int mod>
inline mod_int<_Tp, mod> &operator*=(mod_int<_Tp, mod> &x,
                                     mod_int<_Tp, mod> y) {
    return x.x = (x.x * y.x) % mod, x;
}
#ifdef STL_BITS__2F_STDCx2Bx2Bx2FH
template <typename _Tp, int mod>
inline std::istream &operator>>(std::istream &in, mod_int<_Tp, mod> x) {
    return in >> x.x;
}
template <typename _Tp, int mod>
inline std::ostream &operator>>(std::ostream &out, mod_int<_Tp, mod> x) {
    return out << x.x;
}
#endif

}  // namespace oct