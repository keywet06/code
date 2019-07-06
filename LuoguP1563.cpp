#include <bits/stdc++.h>
const int N = 100000;
int m, n, now, x, y;
int a[N];
std::string s[N];
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        std::cin >> s[i];
        if (a[i]) {
            a[i] = -1;
        } else {
            a[i] = 1;
        }
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        if (x) {
            x = 1;
        } else {
            x = -1;
        }
        now = (now + y % n * a[now] * x + n) % n;
    }
    std::cout << s[now] << std::endl;
    return 0;
}