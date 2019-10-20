#include <bits/stdc++.h>
const int N = 100005;
int ans, n, now;
int bec[N], wa[N], wb[N], cot[N], cha[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &wa[i], &wb[i]);
    }
    bec[1] = 1;
    cot[1] = 1;
    now = wa[1];
    if (wa[now] != 1 && wb[now] != 1) {
        printf("-1\n");
        return 0;
    }
    for (int i = 2; i < n; ++i) {
        bec[i] = now;
        cot[now] = 1;
        if (cot[wa[now]]) {
            if (cot[wb[now]] || (wa[wb[now]] != now && wb[wb[now]] != now)) {
                printf("-1\n");
                return 0;
            }
            now = wb[now];
        } else {
            if (wa[wa[now]] != now && wb[wa[now]] != now) {
                printf("-1\n");
                return 0;
            }
            now = wa[now];
        }
    }
    if (wa[now] != 1 && wb[now] != 1) {
        printf("-1\n");
        return 0;
    }
    memset(cot, 0, sizeof(cot));
    bec[n] = now;
    for (int i = 1; i <= n; ++i) {
        cha[bec[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        ++cot[(cha[i] - i + n) % n];
    }
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, cot[i]);
    }
    memset(cot, 0, sizeof(cot));
    for (int i = 1; i <= n; ++i) {
        cha[bec[n - i + 1]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        ++cot[(cha[i] - i + n) % n];
    }
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, cot[i]);
    }
    printf("%d\n", n - ans);
    return 0;
}