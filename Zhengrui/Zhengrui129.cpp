#include <bits/stdc++.h>

using int64 = long long;

struct node {
    int64 p, d;
    int id;
};

int n;
int64 l, a[100010], b[100010], c[100010];
bool used[100010];
node a1[100010], a2[100010];

bool cmp1(node a, node b) { return a.d == b.d ? a.p < b.p : a.d > b.d; }
bool cmp2(node a, node b) { return a.p > b.p; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> l;
    for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) std::cin >> c[i], c[i] += c[i - 1];
    int64 sum = 0;
    for (int i = 1; i <= n; i++) sum += b[i];
    if (!sum) {
        std::sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++) {
            sum += a[n - i + 1];
            if (sum >= l) return std::cout << i << std::endl, 0;
            if (sum <= c[i]) return std::cout << -1 << std::endl, 0;
        }
        return std::cout << -1 << std::endl, 0;
    }
    for (int i = 1; i <= n; i++) a1[i] = a2[i] = (node){a[i], a[i] - b[i], i};
    std::sort(a1 + 1, a1 + n + 1, cmp1), std::sort(a2 + 1, a2 + n + 1, cmp2);
    int64 h = 0;
    int j = 1;
    for (int i = 1; i <= n; i++) {
        if (h + a2[j].p >= l) return std::cout << i << std::endl, 0;
        h += a1[i].d;
        used[a1[i].id] = 1;
        while (used[a2[j].id]) j++;
    }
    std::cout << -1 << std::endl;
    return 0;
}