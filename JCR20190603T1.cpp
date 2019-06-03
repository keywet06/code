#include <bits/stdc++.h>
class node{
    public:
        int l, r;
};
int cmp1(node, node);
int cmp2(node, node);
const int N = 2005;
const int mod = 1e9 + 7;
char s[N];
int cnt, n, now;
int ha1[N][N], ha2[N][N];
long long ans;
node a[N * N], b[N * N];
int main() {
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            ha1[i][j] = (ha1[i][j - 1] * 26LL + s[j] - 'a') % mod;
        }
    }
    for (int i = n; i >= 1; --i) {
        for (int j = i; j >= 1; --j) {
            ha2[i][j] = (ha2[i][j + 1] * 26LL + s[j] - 'a') % mod;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (ha1[i][j] == ha2[j][i]) {
                ++cnt;
                a[cnt].l = i;
                a[cnt].r = j;
                b[cnt].l = i;
                b[cnt].r = j;
            }
        }
    }
    std::sort(a + 1, a + cnt + 1, cmp1);
    std::sort(b + 1, b + cnt + 1, cmp2);
    now = 1;
    for (int i = 1; i <= cnt; ++i) {
        while (now <= cnt && b[now].l <= a[i].r) {
            ++now;
        }
        ans += cnt - now + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
inline int cmp1(node a, node b) {
    return a.r < b.r;
}
inline int cmp2(node a, node b) {
    return a.l < b.l;
}