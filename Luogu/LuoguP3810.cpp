#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;
const int M = 400005;

int n, k, cnt, ps;
int dt[N], rx[N], ry[N], rz[N], id[N], s[N], rn[N], cp[N], ans[N], xd[N], t[N];

inline void add(int x, int y) {
    while (x <= k) dt[x] += y, x += x & (-x);
}

inline int sum(int x) {
    int ret = 0;
    while (x) ret += dt[x], x &= x - 1;
    return ret;
}

inline void cdq(int x, int y) {
    if (x == y) return;
    int mid = x + y >> 1;
    cdq(x, mid), cdq(mid + 1, y);
    for (int i = x; i <= y; ++i) cp[i] = id[i];
    int l = x, r = mid + 1, d = x;
    while (l <= mid && r <= y) {
        if (ry[cp[l]] <= ry[cp[r]]) {
            add(rz[cp[l]], rn[cp[l]]), id[d++] = cp[l++];
        } else {
            ans[cp[r]] += sum(rz[cp[r]]), id[d++] = cp[r++];
        }
    }
    while (l <= mid) add(rz[cp[l]], rn[cp[l]]), id[d++] = cp[l++];
    while (r <= y) ans[cp[r]] += sum(rz[cp[r]]), id[d++] = cp[r++];
    for (int i = x; i <= mid; ++i) add(rz[cp[i]], -rn[cp[i]]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> rx[i] >> ry[i] >> rz[i], id[i] = i;
    std::sort(id + 1, id + n + 1, [](int x, int y) {
        return rx[x] < rx[y] ||
               (rx[x] == rx[y] &&
                (ry[x] < ry[y] || (ry[x] == ry[y] && rz[x] < rz[y])));
    });
    cnt = 1, ps = 1;
    for (int i = 2; i <= n + 1; ++i) {
        if (rx[id[i]] == rx[id[i - 1]] && ry[id[i]] == ry[id[i - 1]] &&
            rz[id[i]] == rz[id[i - 1]]) {
            ++cnt;
        } else {
            rn[id[i - 1]] = cnt, ans[id[i - 1]] = cnt - 1, cnt = 1;
            for (ps = ps; ps < i; ++ps) xd[id[ps]] = id[i - 1];
        }
    }
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (rn[id[i]]) id[++cnt] = id[i];
    }
    cdq(1, cnt);
    for (int i = 1; i <= n; ++i) ++t[ans[xd[i]]];
    for (int i = 0; i < n; ++i) std::cout << t[i] << '\n';
    return 0;
}