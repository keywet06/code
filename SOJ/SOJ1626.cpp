    #include <bits/stdc++.h>

    #define templ template <typename Type1, typename Type2>
    templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
    templ inline Type1 &Mad(Type1 &x, Type2 y) { return x > y ? x : x = y; }
    #undef templ

    using uint64 = unsigned long long;

    const int N = 10005;

    int n, m[N], k[N], w[N], p[N], Num[N], A[N][N];

    uint64 d;

    uint64 _rand() { return d ^= d << 13, d ^= d >> 7, d ^= d << 17; }

    int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr), std::cout.tie(nullptr);
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            std::cin >> k[i] >> w[i] >> m[i] >> d, p[i] = i, k[i] = n * (n + 1) / 2 - k[i] + 1;
            for (int j = 1; j <= n; ++j) A[i][j] = _rand() % m[i];
        }
        std::sort(p + 1, p + n + 1, [](int i, int j) { return w[i] > w[j]; });
        int Ans = w[p[1]];
        for (int ix = 1, i, *a; ix <= n && (a = A[i = p[ix]], true); ++ix) {
            if (w[i] + m[i] <= Ans) continue;
            for (int j = Ans - w[i] + 1; j <= m[i]; ++j) {
                int Nu = 0, l, r = 0, t = 0;
                for (l = 1; l <= n; ++l) {
                    while (r < n && t < j) ++r, t += !Num[a[r]]++ && a[r] < j;
                    if (t < j) break;
                    Nu += n - r + 1;
                    t -= !--Num[a[l]] && a[l] < j;
                }
                while (l <= r) --Num[a[l++]];
                if (Nu < k[i]) break;
                Mad(Ans, w[i] + j);
            }
        }
        std::cout << Ans << '\n';
        return 0;
    }