#include <bits/stdc++.h>
int ans, n;
std::string s;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> s;
    for (int i = 1; i < n; ++i) {
        ans ^= i;
        for (int j = 0; i + j < n; ++j) {
            if (s[j] != s[i + j] && s[j] != 'g' && s[i + j] != 'g') {
                ans ^= i;
                break;
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}