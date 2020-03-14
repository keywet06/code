#include <bits/stdc++.h>
const int N = 100005;
int ans, n;
int a[N], b[N], c[N];
std::map<int, int> map;
void psort(int l, int r) {
    for (int i = l; i < r; ++i) {
        if (a[i] > a[i + 1]) {
            std::swap(a[i], a[i + 1]);
        }
    }
}
void qsort(int l, int r) {
    if (l == r) return;
    ans += r - l + 1;
    psort(l, r);
    for (int i = l; i <= r; ++i) {
        c[i] = 0;
    }
    int t = l - 1, s = l, p;
    for (int i = l; i <= r; ++i) {
        p = map[a[i]];
        while (c[p]) {
            ++p;
        }
        c[p] = 1;
        while (c[t + 1] && t < r) {
            ++t;
        }
        if (t == i) {
            qsort(s, t);
            s = t + 1;
        }
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    for (int i = n; i; --i) {
        map[a[i]] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
    }
    qsort(1, n);
    std::cout << ans << std::endl;
    return 0;
}