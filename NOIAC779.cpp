#include <bits/stdc++.h>
const int N = 1005;
int T, n, m, flag;
std::string s_1, s_2;
std::string *s1, *s2;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> T;
    s1 = &s_1;
    s2 = &s_2;
    while (T--) {
        std::cin >> n >> m;
        std::cin >> *s1;
        flag = 0;
        for (int i = 1; i < n; ++i) {
            std::cin >> *s2;
            for (int j = 1; j < m; ++j) {
                if (flag || (*s1)[j] == (*s2)[j - 1]) {
                    flag = 1;
                    break;
                }
            }
            std::swap(s1, s2);
        }
        printf(flag ? "Yes\n" : "No\n");
    }
    return 0;
}