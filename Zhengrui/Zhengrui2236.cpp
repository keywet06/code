#include <bits/stdc++.h>

using int64 = long long;
using Pair = std::pair<int, int>;

const int N = 200005;

int n, l, r, Top, n1, n0;
int s[N];

Pair sp[N], tb[N];

std::string str;

inline bool Check(Pair a, Pair b, Pair c) {
    return b.second * int64(a.first - b.first) - int64(a.second - b.second) * (b.first - c.first) >=
           c.second * int64(a.first - b.first);
}

inline int64 Ans(Pair p) { return int64(n0) * p.first + int64(n1) * p.second - 1; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> str;
    for (int i = 0; i < str.size(); ++i) s[i + 1] = s[i] + (str[i] == '1');
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> l >> r, --l;
        sp[i].second = r - l - (sp[i].first = s[r] - s[l] + 1) + 2;
    }
    std::sort(sp, sp + n);
    for (int i = 0; i < n; ++i) {
        while (Top && sp[i].second >= tb[Top].second) --Top;
        while (Top > 1 && Check(tb[Top - 1], tb[Top], sp[i])) --Top;
        tb[++Top] = sp[i];
    }
    tb[0].second = tb[1].second;
    std::cin >> str;
    for (int i = 0; i < str.size(); ++i) s[i + 1] = s[i] + (str[i] == '1');
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> l >> r, --l;
        n1 = s[r] - s[l], n0 = r - l - n1, ++n1, ++n0;
        l = 1, r = Top;
        while (l < r) {
            int Mid = l + r + 1 >> 1;
            if (Ans(tb[Mid - 1]) < Ans(tb[Mid])) {
                l = Mid;
            } else {
                r = Mid - 1;
            }
        }
        std::cout << Ans(tb[l]) << '\n';
    }
    return 0;
}