#include <bits/stdc++.h>
const int N = 1000005;
const int mod = 1e9 + 7;
char a[N];
int T, n, j;
int next[N], ans[N];
long long Ans;
void init();
int Main();
int main() {
    scanf("%d", &T);
    while (T--) {
        init();
        Main();
    }
    return 0;
}
inline void init() {
    memset(next, 0, sizeof(next));
}
inline int Main() {
    scanf("%s", a);
    n = strlen(a);
    j = 0;
    ans[1] = 1;
    for (int i = 1; i < n; ++i) {
        while (j && a[i] != a[j]) {
            j = next[j];
        }
        next[i + 1] = j += a[i] == a[j];
        ans[i + 1] = ans[j] + 1;
    }
    j = 0;
    Ans = 1;
    for (int i = 1; i < n; ++i) {
        while (j && a[i] != a[j]) {
            j = next[j];
        }
        j += a[i] == a[j];
        while (j > ((i + 1) >> 1)) {
            j = next[j];
        }
        (Ans *= ans[j] + 1) %= mod;
    }
    printf("%lld\n", Ans);
    return 0;
}