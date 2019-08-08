#include <bits/stdc++.h>
namespace kw {
    template <typename T> T& tomin(T&, T);
    template <typename T> T& tomax(T&, T);
}
namespace kw {
    template <typename T> inline T& tomin(T& x, T y) {
        return x = std::min(x, y);
    }
    template <typename T> inline T& tomax(T& x, T y) {
        return x = std::max(x, y);
    }
}
const int N = 2e5 + 5;
char t[N], s[N];
int ans, n, now, r;
int al[N], ar[N], d[N];
int main() {
    scanf("%s", t);
    n = strlen(t);
    s[0] = '!';
    for (int i = 0; i < n; ++i) {
        s[i * 2 + 1] = '#';
        s[i * 2 + 2] = t[i];
    }
    s[n * 2 + 1] = '#';
    s[n * 2 + 2] = '@';
    n = n * 2 + 1;
    now = 0;
    r = -1;
    for (int i = 1; i <= n; ++i) {
        d[i] = i > r ? 0 : std::min(r - i, d[2 * now - i]);
        while (s[i - d[i] - 1] == s[i + d[i] + 1]) {
            ++d[i];
        }
        if (i + d[i] > r) {
            r = i + d[i];
            now = i;
        }
        kw::tomax(ar[i - d[i]], d[i]);
        kw::tomax(al[i + d[i]], d[i]);
    }
    for (int i = 2; i <= n; ++i) {
        kw::tomax(ar[i], ar[i - 1] - 1);
    }
    for (int i = n - 1; i; --i) {
        kw::tomax(al[i], al[i + 1] - 1);
    }
    for (int i = 1; i <= n; ++i) {
        if (ar[i] && al[i]) {
            kw::tomax(ans, ar[i] + al[i] + 1);
        }
    }
    printf("%d\n", ans);
    return 0;
}