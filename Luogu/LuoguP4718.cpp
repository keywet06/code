#include <bits/stdc++.h>

using int64 = long long;
using uint64 = unsigned long long;
using int128 = __int128;

std::ostream &operator<<(std::ostream &out, int128 x) {
    return out << int64(x);
}

template <typename Type>
inline Type Abs(const Type x) {
    return x < 0 ? -x : x;
}

template <typename Type>
inline Type Gcd(Type x, Type y) {
    return y ? Gcd(y, x % y) : x;
}

inline std::mt19937_64 GetRand() {
    return std::mt19937_64(
        std::chrono::system_clock::now().time_since_epoch().count());
}

inline uint64 Random(uint64 x, std::mt19937_64 &Rand) { return Rand() % x; }

inline uint64 Random(uint64 l, uint64 r, std::mt19937_64 &Rand) {
    return Random(r - l, Rand) + l;
}

template <typename Type1, typename Type2, typename Type3>
inline Type1 Pow(Type1 x, Type2 m, const Type3 P) {
    Type1 Ret = 1;
    while (m) {
        if (m & 1) Ret = Ret * x % P;
        x = x * x % P, m >>= 1;
    }
    return Ret;
}

const size_t MillerRabinDefaultTestTimes = 16;

template <typename Type>
inline bool MillerRabin(Type n, std::mt19937_64 &Rand,
                        const size_t TestTimes = MillerRabinDefaultTestTimes) {
    if (n < 2 || !(n & 1)) return n == 2;
    Type e = n - 1;
    size_t m = 0;
    while (!(e & 1)) e >>= 1, ++m;
    for (size_t i = 0, j; i < TestTimes; ++i) {
        Type x = Pow(Type(Random(1, n, Rand)), e, n);
        if (x == 1) continue;
        for (j = 0; j < m; ++j) {
            if (x == 1) return false;
            if (x == n - 1) break;
            x = x * x % n;
        }
        if (j == m) return false;
    }
    return true;
}

template <typename Type>
inline bool MillerRabin(Type n,
                        const size_t TestTimes = MillerRabinDefaultTestTimes) {
    std::mt19937_64 Rand(GetRand());
    return MillerRabin(n, Rand, TestTimes);
}

template <typename Type>
inline Type PollardRho(Type n, std::mt19937_64 &Rand) {
    Type s = 0, t = 0, c = Random(1, n, Rand), Val = 1, d;
    for (size_t Step, Len = 1;; Len <<= 1, s = t, Val = 1) {
        for (Step = 0; Step < Len; ++Step) {
            t = (t * t + c) % n;
            Val = Val * Abs(s - t) % n;
            if (!(Step & 127)) {
                d = Gcd(Val, n);
                if (d > 1) return d;
            }
        }
        d = Gcd(Val, n);
        if (d > 1) return d;
    }
}

template <typename Type, typename RetType = std::vector<Type> >
inline RetType GetFac(Type n, std::mt19937_64 &Rand,
                      const size_t TestTimes = MillerRabinDefaultTestTimes) {
    if (n == 1) return RetType();
    if (MillerRabin(n, Rand, TestTimes)) {
        RetType Ret;
        Ret.push_back(n);
        return Ret;
    }
    Type d = PollardRho(n, Rand);
    RetType Ret(GetFac(d, Rand, TestTimes));
    for (Type x : GetFac(n / d, Rand, TestTimes)) Ret.push_back(x);
    return Ret;
}

template <typename Type, typename RetType = std::vector<Type> >
inline RetType GetFac(Type n,
                      const size_t TestTimes = MillerRabinDefaultTestTimes) {
    std::mt19937_64 Rand(GetRand());
    return GetFac(n, Rand, TestTimes);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int64 T, n;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        auto Ans = GetFac(int128(n));
        if (Ans.size() == 1) {
            std::cout << "Prime" << '\n';
            continue;
        }
        std::sort(Ans.begin(), Ans.end());
        std::cout << Ans.back() << '\n';
    }
    return 0;
}