    #include <bits/stdc++.h>
    const __int128 mod = 1e9 + 7;
    long long tmp;
    __int128 n, ans, st, en, a, b, c, d;
    __int128 sum(__int128);
    int main() {
        scanf("%lld", &tmp);
        n = tmp;
        st = (n + 2) / 3;
        en = (n - 1) / 2;
        if (n <= 1e3) {
            for (int i = st; i <= en; ++i) {
                (ans += sum(i)) %= mod;
            }
        } else {
            if ((3 * st - n) & 1) {
                (ans += sum(st)) %= mod;
                ++st;
            }
            if (!((3 * en - n) & 1)) {
                (ans += sum(en)) %= mod;
                --en;
            }
            a = sum(st);
            a += a + 1;
            b = sum(en);
            b += b - 1;
            (ans += (a + b) % mod * (en - st + 1) % mod * 500000004 % mod * 500000004 % mod) %= mod;
        }
        printf("%lld\n", (long long)((ans + mod) % mod));
        return 0;
    }
    inline __int128 sum(__int128 x) {
        return (3 * x - n + 2) / 2 % mod;
    }