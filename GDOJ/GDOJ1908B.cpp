#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define templ template <typename Type1, typename Type2>
templ inline Type1 Min(Type1 x, Type2 y) { return x < y ? x : y; }
templ inline Type1 Max(Type1 x, Type2 y) { return y < x ? x : y; }
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return y < x ? x : x = y; }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 Min(Type1 x, Type2 y, Args... args) { return Min(Min(x, y), args...); }
templ inline Type1 Max(Type1 x, Type2 y, Args... args) { return Max(Max(x, y), args...); }
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

const int N = 500005;
const int M = N << 1;

int n, m;
int a[N], b[N], f[N], s[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= m; ++i) std::cin >> b[i];
    a[n + 1] = INT_MAX - 1;
    for (int i = m + 1; i < M; ++i) b[i] = INT_MAX;
    std::sort(b + 1, b + m + 1);
    memset(f, 1, sizeof(f)), f[0] = 0, s[0] = 1;
    for (int i = 1; i <= n + 1; ++i) {
        /* Binary Search */ {
            int l = 1, r = m + 1, Mid;
            while (l < r) Mid = l + r >> 1, b[Mid] >= a[i] ? r = Mid : l = Mid + 1;
            s[i] = l;
        }
        if (a[i - 1] <= a[i]) f[i] = f[i - 1];
        for (int j = 0; j < i - 1; ++j) {
            if (b[s[j] + i - j - 2] <= a[i]) Mid(f[i], f[j] + i - j - 1);
        }
        for (int j = i - 2; j >= 0; --j) {
            if (b[s[j] + i - j - 2] <= a[i] && f[i] == f[j] + i - j - 1) {
                if (s[j] + i - j - 2 >= s[i]) s[i] = s[j] + i - j - 1;
                break;
            }
        }
    }
    std::cout << (f[n + 1] > n ? -1 : f[n + 1]) << std::endl;
    return 0;
}