
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;
const int mo = 1e9 + 7;
const int maxn = 100010;
int n, cnt, v[maxn], q, m;
long long p[maxn], inv[maxn], now, num[55], dp[55][55];
long long f[maxn >> 1], g[maxn >> 1], h[maxn >> 1];
char s[maxn];
map<char, int> lc;
long long po(long long a, int b) {
    if (b == 0) return 1ll;
    if (b == 1) return a % mo;
    long long c = po(a, b / 2);
    return b & 1 ? c * c % mo * a % mo : c * c % mo;
}
int main() {
    scanf("%s%d", s + 1, &q);
    n = strlen(s + 1);
    p[0] = 1ll;
    m = n / 2;
    for (int i = 1; i <= 100000; i++) p[i] = 1ll * p[i - 1] * i % mo;
    inv[100000] = po(p[100000], mo - 2);
    for (int i = 99999; i >= 0; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % mo;
    for (char i = 'A'; i <= 'Z'; i++) lc[i] = ++cnt;
    for (char i = 'a'; i <= 'z'; i++) lc[i] = ++cnt;
    for (int i = 1; i <= n; i++) v[i] = lc[s[i]], num[v[i]]++;
    now = p[n / 2] % mo * p[n / 2] % mo;
    for (int i = 1; i <= cnt; i++) now = now * inv[num[i]] % mo;
    f[0] = 1;
    for (int j = 1; j <= cnt; j++)
        if (num[j]) {
            for (int i = m; i >= num[j]; i--)
                if (f[i - num[j]]) f[i] = (f[i] + f[i - num[j]]) % mo;
        }
    for (int i = 1; i <= cnt; i++)
        if (num[i]) {
            dp[i][i] = f[m];
            for (int j = 0; j < num[i]; j++) g[j] = f[j];
            for (int j = num[i]; j <= m; j++)
                g[j] = (f[j] - g[j - num[i]] + mo) % mo;
            for (int j = i + 1; j <= cnt; j++)
                if (num[j]) {
                    for (int k = 0; k < num[j]; k++) h[k] = g[k];
                    for (int k = num[j]; k <= m; k++)
                        h[k] = (g[k] - h[k - num[j]] + mo) % mo;
                    dp[i][j] = dp[j][i] = 2ll * h[m] % mo;
                }
        }
    while (q--) {
        int xx, yy;
        scanf("%d%d", &xx, &yy);
        int aa = v[xx], bb = v[yy];
        printf("%lld\n", now * dp[aa][bb] % mo);
    }
    return 0;
}