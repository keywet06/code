#include <bits/stdc++.h>
<<<<<<< HEAD
const int mod = 998244353;
inline void mo(int& x) { x >= mod ? x -= mod : 0; }
inline int mo1(int x) { return x >= mod ? x - mod : x; }
inline int fpow(int x, int n, int ret = 1) {
    for (; n; n >>= 1, x = 1ll * x * x % mod) {
        n& 1 ? ret = 1ll * ret * x % mod : 0;
    }
    return ret;
}
int pw[25], n;
int gbit3(int sta, int x) { return (sta / pw[x - 1]) % 3; }
int ubit3(int x) { return pw[x - 1]; }
int gbit2(int sta, int x) { return (sta >> x) & 1; }
int ubit2(int x) { return pw[x - 1]; }
int f[60005][3], g[60005][3], l[15], r[15];
inline void add(int x, int dx, int c, int d) {
    d += c;
    if (d >= 3) d -= 3;
    mo(g[x + dx][d] += f[x][c]);
}
int main() {
    scanf("%d", &n);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &l[i], &r[i]);
        pw[i] = pw[i - 1] * 3;
    }
    f[0][0] = 1;
    for (int s = 30; s >= 0; --s) {
        for (int x = 0; x < pw[n]; ++x) f[x][1] = f[x][2] = 0;
        for (int i = 1; i <= n; ++i) {
            memset(g, 0, sizeof(g));
            for (int c = 0; c < 3; ++c)
                for (int x = 0; x < pw[n]; ++x) {
                    if (f[x][c] == 0) continue;
                    if ((l[i] ^ r[i]) < 1 << s) {
                        if (gbit3(x, i) == 0) add(x, 0, c, gbit2(l[i], s));
                    } else {
                        if (gbit3(x, i) == 0) {
                            if ((l[i] ^ r[i]) < 1 << s + 1) {
                                add(x, ubit3(i), c, 0);
                                add(x, 2 * ubit3(i), c, 1);
                            } else {
                                add(x, 0, c, 0);
                                add(x, 0, c, 1);
                            }
                        } else if (gbit3(x, i) == 1) {
                            if (gbit2(l[i], s) == 0) {
                                add(x, -ubit3(i), c, 1);
                                add(x, 0, c, 0);
                            } else {
                                add(x, 0, c, 1);
                            }
                        } else {
                            if (gbit2(r[i], s) == 1) {
                                add(x, -2 * ubit3(i), c, 0);
                                add(x, 0, c, 1);
                            } else {
                                add(x, 0, c, 0);
                            }
                        }
                    }
                }
            memcpy(f, g, sizeof(f));
        }
    }
    int ans = 0;
    for (int x = 0; x < pw[n]; ++x) mo(ans += f[x][0]);
    printf("%d\n", ans);
=======
const int N = 105;
int n, K, ans;
int l[N], r[N];
inline void dfs(int c, int sum) {
    if (c > n) {
        ans += !sum;
        return;
    }
    for (int i = l[c]; i <= r[c]; ++i) dfs(c + 1, sum ^ i);
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> l[i] >> r[i];
    dfs(1, 0);
    std::cout << ans << std::endl;
>>>>>>> 406ef0d98a484a2613e66fd396bfc311917cd6ec
    return 0;
}