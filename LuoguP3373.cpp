#include <cmath>
#include <cstdio>
const int maxn = 100005;
long long x, y, o, z, l, temp, ans, n, m, p;
long long belong[maxn], left[maxn], right[maxn], sum[maxn], multiply[maxn],
    plus[maxn], val[maxn], a[maxn];
inline void updata(int x) {
    int y = belong[x];
    for (int i = left[x]; i <= right[x]; ++i) {
        a[i] = (a[i] * multiply[y] + plus[y]) % p;
    }
    multiply[y] = 1;
    plus[y] = 0;
}
template <typename Tp>
Tp min(Tp x, Tp y) {
    return x < y ? x : y;
}
int main() {
    scanf("%d %d %lld", &n, &m, &p);
    l = (int)(sqrt(n));
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        belong[i] = (i + l - 1) / l;
        ++sum[belong[i]];
        right[belong[i]] = i;
        val[belong[i]] += a[i];
    }
    for (int i = n; i > 0; --i) {
        left[belong[i]] = i;
    }
    for (int i = 1; i <= belong[n]; ++i) {
        plus[i] = 0;
        multiply[i] = 1;
    }
    for (int ai = 1; ai <= m; ++ai) {
        scanf("%d", &o);
        if (o == 2) {
            scanf("%d %d %lld", &x, &y, &z);
            updata(x);
            temp = min(right[belong[x]], y);
            for (int i = x; i <= temp; ++i) {
                a[i] += z;
                a[i] %= p;
            }
            val[belong[x]] += z * (temp - x + 1);
            val[belong[x]] %= p;
            if (belong[x] != belong[y]) {
                for (int i = belong[x] + 1; i < belong[y]; ++i) {
                    plus[i] += z;
                    plus[i] %= p;
                    val[i] += z * (right[i] - left[i] + 1);
                    val[i] %= p;
                }
                updata(y);
                for (int i = left[belong[y]]; i <= y; ++i) {
                    a[i] += z;
                    a[i] %= p;
                }
                val[belong[y]] += z * (y - left[belong[y]] + 1);
                val[belong[y]] %= p;
            }
        } else if (o == 1) {
            scanf("%d %d %lld", &x, &y, &z);
            updata(x);
            temp = min(right[belong[x]], y);
            for (int i = x; i <= temp; ++i) {
                val[belong[x]] += a[i] * (z - 1);
                a[i] *= z;
                a[i] %= p;
            }
            val[belong[x]] %= p;
            if (belong[x] != belong[y]) {
                for (int i = belong[x] + 1; i < belong[y]; ++i) {
                    multiply[i] += z;
                    multiply[i] %= p;
                    val[i] *= z;
                    val[i] %= p;
                }
                updata(y);
                for (int i = left[belong[y]]; i <= y; ++i) {
                    val[belong[y]] += a[i] * (z - 1);
                    a[i] *= z;
                    a[i] %= p;
                }
                val[belong[y]] %= p;
            }
        } else {
            scanf("%d %d", &x, &y);
            ans = 0;
            updata(x);
            temp = min(right[belong[x]], y);
            for (int i = x; i <= temp; ++i) {
                ans += a[i];
            }
            ans %= p;
            if (belong[x] != belong[y]) {
                for (int i = belong[x] + 1; i < belong[y]; ++i) {
                    ans += val[i];
                    ans %= p;
                }
                updata(y);
                for (int i = left[belong[y]]; i <= y; ++i) {
                    ans += a[i];
                }
                ans %= p;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
