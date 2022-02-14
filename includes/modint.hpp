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
    inline ModInt() : Data() {}
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
        x.LValue() = this->Value() + Mod - x.Value();
        if (x.Value() >= Mod) x.LValue() -= Mod;
        return *this;
    }
 
    inline CurrentType operator+() { return *this; }
    inline CurrentType operator-() { return 0 - *this; }
 
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
