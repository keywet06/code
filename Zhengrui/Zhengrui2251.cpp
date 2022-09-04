#include <bits/stdc++.h>

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename Type, Type P, typename MulType = Type>
class ModInt {
   protected:
    Type x;

   public:
    using Self = ModInt<Type, P, MulType>;
    ModInt() : x(0) {}
    ModInt(Type c) : x(c) {}
    explicit operator Type() { return x; }
    Type &Data() { return x; }
    friend Self operator+(Self a, Self b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend Self operator-(Self a, Self b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend Self operator*(Self a, Self b) { return MulType(a.x) * b.x % P; }
    friend Self &operator+=(Self &a, Self b) { return (a.x += b.x) >= P ? a.x -= P, a : a; }
    friend Self &operator-=(Self &a, Self b) { return (a.x -= b.x) < 0 ? a.x += P, a : a; }
    friend Self &operator*=(Self &a, Self b) { return a.x = MulType(a.x) * b.x % P, a; }
#define templ template <typename ExpType>
    templ Self Pow(ExpType Exp) {
        Self Base(*this), Ret(1);
        while (Exp) {
            if (Exp & 1) Ret *= Base;
            Base *= Base, Exp >>= 1;
        }
        return Ret;
    }
    templ Self &Pows(ExpType Exp) { return *this = Pow(Exp); }
    templ Self &PowEq(ExpType Exp) { return Pows(Exp); }
    templ Self &PowEqual(ExpType Exp) { return Pows(Exp); }
    templ friend Self Pow(Self Base, ExpType Exp) { return Base.Pow(Exp); }
#undef templ
    Self Inv() { return Pow(P - 2); }
    Self &Invs() { return Pows(P - 2); }
    Self &InvEq() { return Invs(); }
    Self &InvEqual() { return Invs(); }
    friend Self Inv(Self x) { return x.Pow(P - 2); }
    friend Self operator~(Self x) { return x.Inv(); }
    friend Self operator/(Self a, Self b) { return a * ~b; }
    friend Self &operator/=(Self &a, Self b) { return a *= ~b; }
    friend Self &operator++(Self &a) { return a += 1; }
    friend Self &operator--(Self &a) { return a -= 1; }
    friend Self operator++(Self &a, int) {
        Self Tmp = a;
        return a += 1, Tmp;
    }
    friend Self operator--(Self &a, int) {
        Self Tmp = a;
        return a -= 1, Tmp;
    }
    friend Self operator+(Self a) { return a; }
    friend Self operator-(Self a) { return 0 - a; }
    bool operator==(Self a) { return x == int(a); }
};

}  // namespace Oct

#endif

using MInt = Oct::ModInt<int, 998244353, long long>;

const int C = 5;
const int N = 2005;
const int M = N * N;

const MInt R5 = ~MInt(5);

int n, m;
int s[N], Fail[N], Map[N][C];

int TrieTop;
int Trie[M][C], Ban[M][C];

std::string Rs;

MInt Ans;

inline void Dfs(int u, MInt x, bool Flag, int c, int B) {
    x *= R5;
    for (int i = 0; i < C; ++i) {
        int T = std::max(B, Ban[u][i]);
        if (Trie[u][i] > 0) Dfs(Trie[u][i], x, Flag && i == s[c + 1], c + 1, T);
        if (Trie[u][i] == 0 && (!T || Flag && T <= c + 1)) Ans += x;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    std::cin >> Rs;
    for (int i = 1; i <= n; ++i) s[i] = Rs[i - 1] - 'a';
    s[n + 1] = -1;
    TrieTop = 1;
    for (int i = 1; i <= n; ++i) {
        memset(Fail, 0, sizeof(Fail));
        memset(Map, 0, sizeof(Map));
        int Now = 1;
        Map[0][s[i]] = 1;
        for (int j = 1; i + j <= n && j < m; ++j) {
            int c = s[i + j - 1];
            Now = Trie[Now][c] ? Trie[Now][c] : Trie[Now][c] = ++TrieTop;
            Fail[j] = j == 1 ? 0 : Map[Fail[j - 1]][c];
            for (int d = 0; d < C; ++d) Map[j][d] = d == s[i + j] ? j + 1 : Map[Fail[j]][d];
            for (int d = 0; d < C; ++d) {
                if (d != s[i + j] && Map[Fail[j]][s[i + j]]) Ban[Now][d] = std::max(Ban[Now][d], i + j);
            }
            if (j == m - 1 && i + j < n && Map[Map[Fail[j]][s[i + j]]][s[i + j + 1]]) Ban[Now][s[i + j]] = m + 1;
        }
    }
    int Now = 1;
    for (int j = 1; j <= m; ++j) Now = Trie[Now][s[j]] ? Trie[Now][s[j]] : Trie[Now][s[j]] = ++TrieTop;
    Dfs(1, 1, true, 0, 0);
    std::cout << int(Ans) << '\n';
    return 0;
}
