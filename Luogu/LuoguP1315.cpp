#include <bits/stdc++.h>
const long long N = 100005;
long long w, now, n, m, k, x, y, z;
long long d[N], t[N], ti[N], s[N], e[N], head[N], next[N], ends[N], tim[N];
int main() {
    scanf("%lld %lld %lld", &n, &m, &k);
    for (int i = 1; i < n; ++i) {
        scanf("%lld", &d[i]);
    }
    memset(t, -1, sizeof(t));
    for (int i = 1; i <= m; ++i) {
        scanf("%lld %lld %lld", &x, &y, &z);
        if (x > t[y]) {
            if (t[y] != -1) {
                tim[y] += s[y] * (x - t[y]);
            }
            t[y] = x;
        } else {
            tim[y] += t[y] - x;
        }
        ++s[y];
        ++e[z];
        ++w;
        next[w] = head[y];
        head[y] = w;
        ends[w] = z;
    }
    while (k--) {
        now = 0;
        for (int i = 1; i <= n; ++i) {
            ti[i] = now;
            now = std::max(now, t[i]);
            now += d[i];
        }
        now = x = 0;
        y = z = n + 1;
        for (int i = n; i > 1; --i) {
            if (ti[i] <= t[i]) {
                now = 0;
                y = i;
            }
            now += e[i];
            if (d[i - 1] && now > x) {
                x = now;
                z = i - 1;
            }
        }
        --d[z];
    }
    now = x = y = 0;
    for (int i = 1; i < n; ++i) {
        y += d[i - 1] * x;
        now += d[i - 1];
        x -= e[i];
        y += x * (now < t[i] ? t[i] - now : 0) + tim[i];
        y += now > t[i] ? (now - t[i]) * s[i] : 0;
        now = std::max(now, t[i]);
        x += s[i];
    }
    y += d[n - 1] * x;
    printf("%lld\n", y);
    return 0;
}