#include <bits/stdc++.h>
const int B = 2;
const int N = 55;
char c[N], s[N];
char a[N * 2];
int n, t;
int e[B];
int Main() {
    std::cin >> n;
    std::cin >> a;
    for (int i = 0; i < 2 * n - 1; ++i) a[i] -= '0';
    for (int i = 0; i < n; ++i) {
        e[0] = e[1] = 0;
        for (int j = 0; j < n; ++j) {
            if (!c[j]) ++e[a[i + j]];
        }
        s[i] = t = e[1] > e[0];
        for (int j = 0; j < n; ++j) c[i] |= t == a[i + j];
    }
    for (int i = 0; i < n; ++i) s[i] += '0';
    std::cout << s << std::endl;
    return 0;
}
int main() {
    int T;
    std::cin >> T;
    while (T--) {
        memset(c, 0, sizeof(c));
        memset(s, 0, sizeof(s));
        memset(a, 0, sizeof(a));
        memset(e, 0, sizeof(e));
        Main();
    }
    return 0;
}