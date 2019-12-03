#include <bits/stdc++.h>
const int N = 1000005;
char a[N];
int n, now;
int next[N];
int main() {
    scanf("%s", a + 1);
    n = strlen(a + 1);
    for (int i = 2; i <= n; ++i) {
        next[i] = next[i - 1];
        while (next[i] && a[next[i]] != a[i]) {
            next[i] = next[next[i]];
        }
        next[i] += a[next[i]] == a[i];
    }
    now = 0;
    for (int i = 2; i <= n; ++i) {
        while (now && a[now + 1] != a[i]) {
            now = next[now];
        }
        now += a[now + 1] == a[i];
    }
    printf("%d\n", n - now);
    return 0;
}