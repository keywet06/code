#include <bits/stdc++.h>
char str[100];
long long n, x, xb;
long long ans, tmp, left, right, middle;
inline long long check(long long x) {
    ans = 0;
    tmp = x;
    while (tmp) {
        ans += tmp;
        tmp /= 2;
    }
    return ans;
}
inline long long getans(long long x) {
    left = std::max(1ll, x / 2 - 100);
    right = std::min(1000000000000000000ll, x / 2 + 100);
    while (left <= right) {
        middle = left + right >> 1;
        tmp = check(middle) - x;
        if (tmp < 0) {
            left = middle + 1; 
        } else if (tmp > 0) {
            right = middle - 1;
        } else {
            return middle;
        }
    }
    return 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        x = getans(x);
        if (!x) {
            std::cout << "Impossible\n";
        } else {
            xb = 0;
            while (x > 1) {
                if (x % 2) {
                    str[++xb] = 'R';
                } else {
                    str[++xb] = 'L';
                }
                x /= 2;
            }
            std::cout << "S";
            for (int i = xb; i; --i) {
               std::cout << str[i];
            }
            std::cout << "\n";
        }
    }
    return 0;
}