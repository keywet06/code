#include <bits/stdc++.h>
const int N = 105;
const int Z = 1000005;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
int cnt, n, m;
long long res1, res2, as1, as2;
long long m1[N], m2[N];
long long ans[Z];
std::string s;
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i <= n; ++i) {
        std::cin >> s;
        if (s[0] != '-') {
            for (int j = 0; j < s.length(); ++j) {
                (m1[i] = m1[i] * 10 + s[j] - '0') %= mod1;
            }
            for (int j = 0; j < s.length(); ++j) {
                (m2[i] = m2[i] * 10 + s[j] - '0') %= mod2;
            }
        } else {
            for (int j = 1; j < s.length(); ++j) {
                (m1[i] = m1[i] * 10 + s[j] - '0') %= mod1;
            }
            m1[i] = mod1 - m1[i];
            for (int j = 1; j < s.length(); ++j) {
                (m2[i] = m2[i] * 10 + s[j] - '0') %= mod2;
            }
            m2[i] = mod2 - m2[i];
        }
    }
    for (int i = 1; i <= m; ++i) {
        res1 = 1;
        as1 = m1[0];
        for (int j = 1; j <= n; ++j) {
            (res1 *= i) %= mod1;
            (as1 += m1[j] * res1) %= mod1;
        }
        res2 = 1;
        as2 = m2[0];
        for (int j = 1; j <= n; ++j) {
            (res2 *= i) %= mod2;
            (as2 += m2[j] * res2) %= mod2;
        }
        if (!as1 && !as2) {
            ans[++cnt] = i;
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; ++i) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}