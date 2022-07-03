#include <bits/stdc++.h>

#define templ template <typename Type1, typename Type2>
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : (x = y); }
templ inline Type2 &Mad(Type1 &x, Type2 y) { return x > y ? x : (x = y); }
#undef templ

using int64 = long long;

const int N = 1000005;

int n;
int a[N];

int64 Sum, Ans;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 0, x; i < n; ++i) std::cin >> x, ++a[x], Sum += x;
    for (int i = N - 2; i >= 0; --i) a[i] += a[i + 1];
    for (int i = 2; i < N; ++i) {
        int64 s = 0;
        for (int j = i; j < N; j += i) s += a[j];
        Mad(Ans, s * (i - 1));
    }
    std::cout << Sum - Ans << std::endl;
    return 0;
}