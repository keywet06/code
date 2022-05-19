#include <bits/stdc++.h>

const int C = 30;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    int Ans = 0, Flag = true, m0 = 0, m1 = (1 << C) - 1;
    for (int i = 0, x; i < n; ++i) {
        std::string Oper;
        std::cin >> Oper >> x;
        if (Oper[0] == 'O') {
            m0 |= x, m1 |= x;
        } else if (Oper[0] == 'X') {
            m0 ^= x, m1 ^= x;
        } else {
            m0 &= x, m1 &= x;
        }
    }
    for (int t = 1 << C; t; t >>= 1) {
        if (!Flag) {
            Ans |= (m0 | m1) & t;
        } else if (m & t) {
            Ans |= (m0 & t) >= (m1 & t) ? Flag = false, m0 & t : m1 & t;
        } else {
            Ans |= m0 & t;
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}