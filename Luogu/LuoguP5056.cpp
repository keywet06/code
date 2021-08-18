#include <bits/stdc++.h>

using int64 = long long;

const int64 N = 13;
const int64 H = 299987;

int64 n, m, ex, ey, now, last, ans;
int64 a[N][N], head[300000], next[2 << 24], que[2][2 << 24], val[2][2 << 24],
    cnt[2], inc[13];
inline void init() {
    scanf("%lld%lld", &n, &m);
    for (int64 i = 1; i <= n; ++i) {
        char s[100];
        scanf(" %s", s + 1);
        for (int64 j = 1; j <= m; ++j) {
            if (s[j] == '.') {
                a[i][j] = 1;
                ex = i;
                ey = j;
            }
        }
    }
    inc[0] = 1;
    for (int64 i = 1; i <= 13; ++i) inc[i] = inc[i - 1] << 2;
}
inline void insert(int64 bit, int64 num) {
    int64 u = bit % H + 1;
    for (int64 i = head[u]; i; i = next[i]) {
        if (que[now][i] == bit) {
            val[now][i] += num;
            return;
        }
    }
    next[++cnt[now]] = head[u];
    head[u] = cnt[now];
    que[now][cnt[now]] = bit;
    val[now][cnt[now]] = num;
}
inline void work() {
    cnt[now] = 1;
    val[now][1] = 1;
    que[now][1] = 0;
    for (int64 i = 1; i <= n; ++i) {
        for (int64 j = 1; j <= cnt[now]; ++j) que[now][j] <<= 2;
        for (int64 j = 1; j <= m; ++j) {
            memset(head, 0, sizeof(head));
            last = now;
            now ^= 1;
            cnt[now] = 0;
            for (int64 k = 1; k <= cnt[last]; ++k) {
                int64 bit = que[last][k], num = val[last][k];
                int64 b1 = (bit >> ((j - 1) * 2)) % 4,
                      b2 = (bit >> (j * 2)) % 4;
                if (!a[i][j]) {
                    if (!b1 && !b2) insert(bit, num);
                } else if (!b1 && !b2) {
                    if (a[i + 1][j] && a[i][j + 1])
                        insert(bit + inc[j - 1] + inc[j] * 2, num);
                } else if (!b1 && b2) {
                    if (a[i][j + 1]) insert(bit, num);
                    if (a[i + 1][j])
                        insert(bit - inc[j] * b2 + inc[j - 1] * b2, num);
                } else if (b1 && !b2) {
                    if (a[i + 1][j]) insert(bit, num);
                    if (a[i][j + 1])
                        insert(bit - inc[j - 1] * b1 + inc[j] * b1, num);
                } else if (b1 == 1 && b2 == 1) {
                    int64 k1 = 1;
                    for (int64 l = j + 1; l <= m; ++l) {
                        if ((bit >> (l * 2)) % 4 == 1) ++k1;
                        if ((bit >> (l * 2)) % 4 == 2) --k1;
                        if (!k1) {
                            insert(bit - inc[j] - inc[j - 1] - inc[l], num);
                            break;
                        }
                    }
                } else if (b1 == 2 && b2 == 2) {
                    int64 k1 = 1;
                    for (int64 l = j - 2; l >= 0; --l) {
                        if ((bit >> (l * 2)) % 4 == 1) --k1;
                        if ((bit >> (l * 2)) % 4 == 2) ++k1;
                        if (!k1) {
                            insert(bit - inc[j] * 2 - inc[j - 1] * 2 + inc[l],
                                   num);
                            break;
                        }
                    }
                } else if (b1 == 2 && b2 == 1) {
                    insert(bit - inc[j - 1] * 2 - inc[j], num);
                } else if (i == ex && j == ey) {
                    ans += num;
                }
            }
        }
    }
}
int main() {
    init();
    work();
    printf("%lld", ans);
    return 0;
}