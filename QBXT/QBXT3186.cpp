#include <bits/stdc++.h>

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename DataType, DataType Mod, typename OperType = DataType>
class ModInt {
   public:
    using CurrentType = ModInt<DataType, Mod, OperType>;
    using ThisType = CurrentType;

   protected:
    DataType Data;

   public:
    inline ModInt() : Data(0) {}
    inline ModInt(const DataType Val) : Data(Val) {}

    inline const DataType Value() const { return this->Data; }
    inline DataType &LValue() { return this->Data; }

    inline bool operator==(CurrentType x) const {
        return this->Value() == x.Value();
    }
    inline bool operator!=(CurrentType x) const {
        return this->Value() != x.Value();
    }

    inline CurrentType operator+(CurrentType x) const {
        return (x.LValue() += this->Value()) >= Mod ? x.Value() - Mod
                                                    : x.Value();
    }
    inline CurrentType &operator+=(CurrentType x) {
        if ((this->LValue() += x.Value()) >= Mod) this->LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator-(CurrentType x) const {
        x.LValue() = this->Value() + Mod - x.Value();
        return x.Value() >= Mod ? x.Value() - Mod : x.Value();
    }
    inline CurrentType &operator-=(CurrentType x) {
        this->LValue() += Mod - x.Value();
        if (this->Value() >= Mod) this->LValue() -= Mod;
        return *this;
    }

    inline CurrentType operator+() { return *this; }
    inline CurrentType operator-() { return CurrentType(0) - *this; }

    inline CurrentType operator*(CurrentType x) const {
        return this->Value() * OperType(x.Value()) % Mod;
    }
    inline CurrentType &operator*=(CurrentType x) {
        this->LValue() = this->Value() * OperType(x.Value()) % Mod;
        return *this;
    }

    inline CurrentType Pow(DataType Exp) const {
        CurrentType x = *this, ret = 1;
        while (Exp) {
            if (Exp & 1) ret *= x;
            x *= x, Exp >>= 1;
        }
        return ret;
    }

    inline CurrentType Inv() const { return this->Pow(Mod - 2); }

    inline CurrentType operator/(CurrentType x) const {
        return *this * x.Inv();
    }
    inline CurrentType &operator/=(CurrentType x) { return *this *= x.Inv(); }
};

}  // namespace Oct

#endif

using uint64 = unsigned long long;

class BigInt {
   public:
    std::vector<int> v;

    using Iterator = std::vector<int>::iterator;
    using iterator = Iterator;

    inline BigInt() { v.push_back(0); }

    inline BigInt(uint64 x) {
        if (!x) v.push_back(0);
        while (x) v.push_back(x % 10), x /= 10;
    }

    inline BigInt(std::string s) {
        v.resize(s.size());
        for (size_t i = 0; i < s.size(); ++i) v[s.size() - i - 1] = s[i] - '0';
    }

    inline size_t Size() { return v.size(); }

    inline void Swap(BigInt &x) { v.swap(x.v); }

    inline void Resize(size_t x) { v.resize(x); }

    inline iterator Begin() { return v.begin(); }
    inline iterator begin() { return Begin(); }

    inline iterator End() { return v.end(); }
    inline iterator end() { return End(); }

    inline int &Back() { return v.back(); }

    inline int &DBack() { return v[Size() - 2]; }

    inline void Push(int x) { v.push_back(x); }

    inline void Pop() { v.pop_back(); }

    inline void Erase0() {
        while (Size() > 0 && !Back()) Pop();
    }

    inline int &operator[](size_t x) { return v[x]; }
};

inline BigInt operator+(BigInt A, BigInt B) {
    BigInt Ret;
    if (A.Size() < B.Size()) A.Swap(B);
    Ret.Resize(A.Size());
    for (size_t i = 0; i < B.Size(); ++i) Ret[i] = A[i] + B[i];
    for (size_t i = B.Size(); i < A.Size(); ++i) Ret[i] = A[i];
    for (size_t i = 0; i + 1 < Ret.Size(); ++i) {
        if (Ret[i] > 9) Ret[i] -= 10, ++Ret[i + 1];
    }
    while (Ret.Back() > 9) Ret.Back() -= 10, Ret.Push(1);
    return Ret;
}

inline BigInt operator*(BigInt A, BigInt B) {
    BigInt Ret;
    Ret.Resize(A.Size() + B.Size());
    for (size_t i = 0; i < A.Size(); ++i) {
        for (size_t j = 0; j < B.Size(); ++j) Ret[i + j] += A[i] * B[j];
    }
    for (size_t i = 0; i + 1 < Ret.Size(); ++i) {
        if (Ret[i] > 9) Ret[i + 1] += Ret[i] / 10, Ret[i] %= 10;
    }
    while (Ret.Back() > 9) Ret.Push(Ret.Back() / 10), Ret.DBack() %= 10;
    Ret.Erase0();
    return Ret;
}

using int32 = int_fast32_t;

const int32 P = 10007;

using MInt = Oct::ModInt<int32, P>;

MInt Ans;

BigInt x;

std::string s;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> s, x = s;
    x = x * (x + 1) * (x + 2);
    for (int i = x.Size() - 1; i >= 0; --i) Ans = Ans * 10 + x[i];
    std::cout << (Ans / 6).Value() << std::endl;
    return 0;
}
