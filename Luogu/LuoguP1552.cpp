#include <bits/stdc++.h>
const int N = 100005;
int n, m, x;
int size[N], fa[N], root[N], val[N], dis[N], left[N], right[N];
long long ans;
long long sum[N], lead[N];
inline int merge(int a, int b) {
    if (!a || !b) return a + b;
    if (val[a] < val[b]) std::swap(a, b);
    right[a] = merge(right[a], b);
    if (dis[left[a]] < dis[right[a]]) std::swap(left[a], right[a]);
    dis[a] = dis[right[a]] + 1;
    return a;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> fa[i] >> val[i] >> lead[i];
        root[i] = i;
        sum[i] = val[i];
        size[i] = 1;
        ans = std::max(ans, lead[i]);
    }
    for (int i = n; i; --i) {
        root[fa[i]] = merge(root[fa[i]], root[i]);
        size[fa[i]] += size[i];
        sum[fa[i]] += sum[i];
        while (sum[fa[i]] > m) {
            sum[fa[i]] -= val[root[fa[i]]];
            root[fa[i]] = merge(left[root[fa[i]]], right[root[fa[i]]]);
            --size[fa[i]];
        }
        ans = std::max(ans, size[fa[i]] * lead[fa[i]]);
    }
    std::cout << ans << std::endl;
    return 0;
}