#include <bits/stdc++.h>

using int64 = long long;

const int N = 100005;
const int M = N << 1;

char ch[N], s[M];

int n;
int len[M], l[M], r[M];

void manache() {
    int id = 0, maxx = 0;
    for (int i = 1; i <= n; ++i) {
        len[i] = i < maxx ? std::min(maxx - i, len[id * 2 - i]) : 1;
        while (s[i + len[i]] == s[i - len[i]]) ++len[i];
        if (i + len[i] > maxx) maxx = i + len[i], id = i;
        l[i + len[i] - 1] = std::max(l[i + len[i] - 1], len[i] - 1);
        r[i - len[i] + 1] = std::max(r[i - len[i] + 1], len[i] - 1);
    }
}

int main() {
    scanf("%s", ch + 1);
    int tlen = strlen(ch + 1);
    s[0] = '$', s[1] = '#', n = 1;
    for (int i = 1; i <= tlen; ++i) s[++n] = ch[i], s[++n] = '#';
    manache();
    for (int i = 3; i <= n; i += 2) r[i] = std::max(r[i], r[i - 2] - 2);
    for (int i = n; i >= 3; i -= 2) l[i] = std::max(l[i], l[i + 2] - 2);
    int ans = 0;
    for (int i = 3; i <= n; i += 2) {
        if (r[i] && l[i]) ans = std::max(ans, l[i] + r[i]);
    }
    printf("%d\n", ans);
    return 0;
}