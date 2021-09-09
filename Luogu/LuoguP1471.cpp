#include <bits/stdc++.h>

const int N = 100005;
const int M = 262144;

int n, m, o, x, y;

double v, t;
double a[N];
double ta[M], sum[M], ans[M];

void pushup(int u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
    ans[u] = ans[u << 1] + ans[u << 1 | 1];
}

void build(int u, int l, int r) {
    if (l == r) return sum[u] = a[l], ans[u] = a[l] * a[l], void(0);
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r), pushup(u);
}

void add(int u, int l, int r, double val) {
    ans[u] += 2 * val * sum[u] + val * val * (r - l + 1);
    ta[u] += val, sum[u] += (r - l + 1) * val;
    return;
}

void pushdown(int u, int l, int r) {
    if (ta[u] == 0) return;
    int mid = l + r >> 1;
    add(u << 1, l, mid, ta[u]), add(u << 1 | 1, mid + 1, r, ta[u]), ta[u] = 0;
    return;
}

void modify(int u, int l, int r, int x, int y, double val) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return add(u, l, r, val);
    int mid = l + r >> 1;
    pushdown(u, l, r);
    modify(u << 1, l, mid, x, y, val);
    modify(u << 1 | 1, mid + 1, r, x, y, val);
    pushup(u);
    return;
}

double query1(int u, int l, int r, int x, int y) {
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    return query1(u << 1, l, mid, x, y) + query1(u << 1 | 1, mid + 1, r, x, y);
}

double query2(int u, int l, int r, int x, int y) {
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return ans[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    return query2(u << 1, l, mid, x, y) + query2(u << 1 | 1, mid + 1, r, x, y);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout << std::fixed << std::setprecision(4);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        std::cin >> o, std::cin >> x >> y;
        if (o == 1) {
            std::cin >> v, modify(1, 1, n, x, y, v);
        } else if (t = query1(1, 1, n, x, y) / (y - x + 1), o == 2) {
            std::cout << t << "\n";
        } else {
            std::cout << -t * t + query2(1, 1, n, x, y) / (y - x + 1) << "\n";
        }
    }
    return 0;
}
