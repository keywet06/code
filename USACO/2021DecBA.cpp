#include <bits/stdc++.h>

using int64 = long long;

const int N = 500005;
const int Z = int('G') + int('H');

char s[N];

int n, l, r;

int64 ans;

int main() {
    std::cin >> n >> s + 1;
    for (int i = 1; i <= n; ++i) {
        l = r = i;
        while (s[l - 1] == Z - s[i]) --l;
        while (s[r + 1] == Z - s[i]) ++r;
        ans += int64(i - l + 1) * (r - i + 1) - (l < i) - (r > i) - 1;
    }
    std::cout << ans << std::endl;
    return 0;
}