#include <bits/stdc++.h>
const int __MillerRabin_pnum = 10;
const int __MillerRabin_pri[10] = {2, 3, 5, 7, 11, 13, 101, 1009, 3001, 3011};
template <typename __Tp>
  inline __Tp power(__Tp x, int y, __Tp mod) {
    return y == 1 ? x : (y & 1 ? power(x * x % mod, y >> 1, mod) * x % mod :
      power(x * x % mod, y >> 1, mod));
}
template <typename __Tp>
  inline __Tp gcd(__Tp x, __Tp y) {
    return y ? gcd(y, x % y) : x;
}
static class MillerRabin_type {
   protected:
    inline int check(int p, int x) {
        if (p == x) {
            return 0;
        }
        if (power(p, x, x - 1) != 1) {
            return 1;
        }
        int k = x - 1, t;
        while (!(k & 1)) {
            k /= 2;
            t = power(p, k, x);
            if (t != 1 && t != p - 1) {
                return 1;
            }
            if (t == p - 1) {
                return 0;
            }
        }
        return 0;
    }
   public:
    inline int operator () (int x) {
        for (int i = 0; i < __MillerRabin_pnum; ++i) {
            if (check(__MillerRabin_pri[i], x)) {
                return 1;
            }
        }
        return 0;
    }
} MillerRabin;
static class PollardRho_type {
   public:
    std::mt19937 random;
    PollardRho_type() {
        std::mt19937 tmp(unsigned(
          std::chrono::system_clock::now().time_since_epoch().count()));
        random = tmp;
    }
} PollardRho;
int main() {
    MillerRabin(1);
    return 0;
}