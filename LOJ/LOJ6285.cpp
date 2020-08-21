#include <bits/stdc++.h>
const int N = 150000;
const int S = 350;
class query {
   public:
    int id, l, r;
};
int n, cnt, max, re, smax, sre, l, r;
int a[N], s[N], p[N], ans[N];
query q[N];
inline int id(int x) { return x / S; }
inline int begins(int x) { return id(x) * S; }
inline int ends(int x) { return id(x) * S + S; }
inline int cmp(query x, query y) {
    return id(x.l) != id(y.l) ? id(x.l) < id(y.l) : x.r < y.r;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i], s[i] = a[i];
    std::sort(s, s + n);
    int cnt = std::unique(s, s + n) - s;
    for (int i = 0; i < n; ++i) a[i] = std::lower_bound(s, s + cnt, a[i]) - s;
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> l >> r;
        --l, --r;
        if (id(l) == id(r)) {
            max = re = 0;
            for (int j = l; j <= r; ++j) {
                if (++p[a[j]] > max || (p[a[j]] == max && a[j] < re)) {
                    max = p[a[j]];
                    re = a[j];
                }
            }
            ans[i] = re;
            for (int j = l; j <= r; ++j) --p[a[j]];
            continue;
        }
        q[cnt].l = l;
        q[cnt].r = r;
        q[cnt].id = i;
        ++cnt;
    }
    std::sort(q, q + cnt, cmp);
    l = 0, r = -1;
    for (int i = 0; i < cnt; ++i) {
        if (!i || id(q[i - 1].l) < id(q[i].l)) {
            while (l <= r) --p[a[r--]];
            max = re = smax = sre = 0;
            l = ends(q[i].l);
            r = ends(q[i].l) - 1;
        }
        while (r < q[i].r) {
            ++p[a[++r]];
            if (p[a[r]] > max || (p[a[r]] == max && a[r] < re)) {
                max = p[a[r]];
                re = a[r];
            }
        }
        smax = max, sre = re;
        while (l > q[i].l) {
            ++p[a[--l]];
            if (p[a[l]] > max || (p[a[l]] == max && a[l] < re)) {
                max = p[a[l]];
                re = a[l];
            }
        }
        ans[q[i].id] = re;
        while (l < ends(q[i].l)) --p[a[l++]];
        max = smax, re = sre;
    }
    for (int i = 0; i < n; ++i) std::cout << s[ans[i]] << '\n';
    return 0;
}