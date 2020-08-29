#include <bits/stdc++.h>
const int N = 201;
int n, num0, num1, num2;
int a[N], b[N], num[N], vis[N];
int main() {
    std::cin >> n;
    n <<= 1;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], ++num[a[i]];
    for (int i = 1; i <= n; ++i) {
        if (num[a[i]] >= 2) {
            if (!vis[a[i]]) {
                num0++;
                b[i] = vis[a[i]] = 1;
            } else if (vis[a[i]] == 1)
                b[i] = vis[a[i]] = 2;
        } else if (num1 > num2) {
            b[i] = 2;
            num2++;
        } else {
            b[i] = 1;
            num1++;
        }
    }
    num1 += num0;
    std::cout << num1 * (num2 + num0) << std::endl;
    int n1 = n >> 1;
    for (int i = 1; i <= n; ++i) {
        if (vis[a[i]] == 2 && !b[i]) {
            if (num1 < n1) {
                b[i] = 1;
                num1++;
            } else {
                b[i] = 2;
            }
        }
    }
    for (int i = 1; i <= n; ++i) std::cout << b[i] << ' ';
    std::cout << std::endl;
    return 0;
}