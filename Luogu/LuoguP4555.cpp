#include <bits/stdc++.h>
const int N = 3e5 + 5;
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
        ar[i - d[i]] = std::max(ar[i - d[i]], d[i]);
        al[i + d[i]] = std::max(al[i + d[i]], d[i]);
    }
    for (int i = 2; i <= n; ++i) {
        ar[i] = std::max(ar[i], ar[i - 1] - 1);
    }
    for (int i = n - 1; i; --i) {
        al[i] = std::max(al[i], al[i + 1] - 1);
    }
    for (int i = 1; i < n; ++i) {
        if ((al[i] + 1 - i % 2) && (ar[i + 1] + i % 2)) {
            ans = std::max(ans, al[i] + ar[i + 1] + 1);
        }
    }
    printf("%d\n", ans);
    return 0;
}