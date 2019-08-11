#include <bits/stdc++.h>
const int N = 20005;
char str[N], strt[N];
int T, n, q, opt, x, y, z, m;
int Main();
int main() {
    scanf("%d", &T);
    while (T--) {
        Main();
    }
    return 0;
}
inline int Main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; ++i) {
        str[i] -= '0';
    }
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &opt);
        if (opt == 1) {
            scanf("%d %d %d", &x, &y, &z);
            for (int i = x; i <= y; ++i) {
                str[i] = z;
            }
        } else if (opt == 2) {
            scanf("%d", &x);
            for (int i = 1; i <= n; ++i) {
                strt[i] = str[i];
            }
            for (int i = 1; i <= x; ++i) {
                str[n - x + i] = strt[i];
            }
            for (int i = 1; i <= n - x; ++i) {
                str[i] = strt[i + x];
            }
        } else if (opt == 3) {
            scanf("%d %d", &x, &y);
            for (int i = x; i <= y; ++i) {
                str[i] ^= 1;
            }
        } else {
            scanf("%d %d %s", &x, &y, strt + 1);
            m = strlen(strt + 1);
            z = 0;
            for (int i = x; i <= y - m + 1; ++i)  {
                opt = 1;
                for (int j = 1; j <= m; ++j) {
                    if (str[i + j - 1] != strt[j] - '0') {
                        opt = 0;
                        break;
                    }
                }
                z += opt;
            }
            printf("%d\n", z);
        }
    }
    return 0;
}