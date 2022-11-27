#include <bits/stdc++.h>

const int N = 300005;

int n, Cnt, Sta[N];

std::string s;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> s;
    for (int i = 1, x, c = s[0] == 'W', m = 0; i <= n; ++i) {
        std::cin >> x;
        if ((s[i - 1] == 'W') == c) {
            m = std::max(m, x);
        } else {
            c ^= 1, Sta[Cnt++] = m, m = x;
        }
    }
    std::sort(Sta + 1, Sta + Cnt, std::greater<int>());
    long long Ans = 0;
    for (int i = 1; i << 1 <= Cnt; ++i) Ans += Sta[i];
    std::cout << Ans << '\n';
    return 0;
}