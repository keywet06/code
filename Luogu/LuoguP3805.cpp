#include <bits/stdc++.h>

const int N = 21000002;

char data[N];

int cnt, ans;
int p[N];

int main() {
    char c = getchar();
    data[0] = '~', data[cnt = 1] = '|';
    while (c < 'a' || c > 'z') c = getchar();
    while (c >= 'a' && c <= 'z') {
        data[++cnt] = c, data[++cnt] = '|', c = getchar();
    }
    for (int t = 1, r = 0, mid = 0; t <= cnt; ++t) {
        if (t <= r) p[t] = std::min(p[(mid << 1) - t], r - t + 1);
        while (data[t - p[t]] == data[t + p[t]]) ++p[t];
        if (p[t] + t > r) r = p[t] + t - 1, mid = t;
        if (p[t] > ans) ans = p[t];
    }
    printf("%d\n", ans - 1);
    return 0;
}