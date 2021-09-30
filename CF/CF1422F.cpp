#include <bits/stdc++.h>

using int64 = long long;
using pair = std::pair<int, int>;

const int C = 20;
const int D = 450;
const int P = 1000000007;

template <int _MaxPrime>
inline std::vector<int> getprime() {
    std::bitset<_MaxPrime> a;
    std::vector<int> ret;
    for (int i = 2; i < D; ++i) {
        if (!a[i]) ret.push_back(i);
        for (int x : ret) {
            if (x * i >= D) break;
            a[x * i] = 1;
            if (i % x == 0) break;
        }
    }
    return ret;
}

inline int64 power(int64 x, int y) {
    int64 ret = 1;
    while (y) {
        if (y & 1) ret = ret * x % P;
        x = x * x, y >>= 1;
    }
}

inline std::vector<int> solve(std::vector<int> a, std::vector<pair> b) {
    auto pr = getprime<D>();
    int n = a.size(), m = pr.size(), q = b.size();
    char st[m][n][C];
    int ia[n];
    std::vector<int> ret;
    for (int r = 0; r < m; ++r) {
        for (int i = 0; i < n; ++i) {
            st[r][i][0] = 0;
            while (a[i] % pr[r] == 0) a[i] /= pr[r], ++st[r][i][0];
        }
    }
    for (int r = 0; r < m; ++r) {
        for (int c = 1; c < C; ++c) {
            int _n = n - (1 << c), _c = c - 1, _d = 1 << _c;
            for (int i = 0; i <= _n; ++i) {
                st[r][i][c] = std::max(st[r][i][_c], st[r][i + _d][_c]);
            }
        }
    }
    
    return ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);

    return 0;
}