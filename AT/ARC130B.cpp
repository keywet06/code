#include <bits/stdc++.h>

using int64 = long long;

const int N = 300005;

int h, w, k, q;
int t[N], n[N], c[N];

int64 ans[N];

std::set<int> he, we;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> h >> w >> k >> q;
    for (int i = q; i; --i) std::cin >> t[i] >> n[i] >> c[i];
    for (int i = 1; i <= q; ++i) {
        if (t[i] == 1) {
            if (he.count(n[i])) continue;
            ans[c[i]] += w - we.size(), he.insert(n[i]);
        } else {
            if (we.count(n[i])) continue;
            ans[c[i]] += h - he.size(), we.insert(n[i]);
        }
    }
    for (int i = 1; i <= k; ++i) std::cout << ans[i] << " \n"[i == k];
    return 0;
}
