#include <bits/stdc++.h>

using int64 = long long;

const int N = 300005;
const int M = N << 1;

int n, x, y, z, s, t;
int a[N], max[N], min[N];
int c[M], d[M];

bool p(int x, int l, int r) { return x >= l && x <= r; }

void solve(int l, int r) {
    // std::cerr << "solve(" << l << ", " << r << "): (";
    int temp = s;
    if (l == r) return /* std::cerr << 1 << ")" << std::endl, */ void(++s);
    int m = l + r >> 1;
    max[m] = min[m] = a[m];
    for (int i = m - 1; i >= l; --i) {
        max[i] = std::max(a[i], max[i + 1]);
        min[i] = std::min(a[i], min[i + 1]);
    }
    max[m + 1] = min[m + 1] = a[m + 1];
    for (int i = m + 2; i <= r; ++i) {
        max[i] = std::max(a[i], max[i - 1]);
        min[i] = std::min(a[i], min[i - 1]);
    }
    for (int i = 1; i <= m; ++i) {
        x = max[i] - min[i];
        s += p(i + x, m + 1, r) && max[i + x] <= max[i] && min[i + x] >= min[i];
    }
    // std::cerr << s - temp << ", ", temp = s;
    for (int i = m + 1; i <= r; ++i) {
        x = max[i] - min[i];
        s += p(i - x, l, m) && max[i - x] <= max[i] && min[i - x] >= min[i];
    }
    // std::cerr << s - temp << ", ", temp = s;
    ++t, x = y = m;
    for (int i = m + 1; i <= r; ++i) {
        while (x >= l && max[x] < max[i]) {
            if (d[z = x - min[x] + N] < t) d[z] = t, c[z] = 0;
            ++c[z], --x;
        }
        while (y >= x && min[y] > min[i]) --c[y - min[y] + N], --y;
        s += d[z = i - max[i] + N] == t ? c[z] : 0;
    }
    // std::cerr << s - temp << ", ", temp = s;
    ++t, x = y = m;
    for (int i = m + 1; i <= r; ++i) {
        while (x >= l && min[x] > min[i]) {
            if (d[z = x + max[x] + N] < t) d[z] = t, c[z] = 0;
            ++c[z], --x;
            // std::cout << "(" << z - N << ", ";
        }
        while (y >= x && max[y] < max[i]) --c[y + max[y] + N], --y;
        s += d[z = i + min[i] + N] == t ? c[z] : 0;
        // std::cerr << (i + min[i]) << ")";
    } 
    // std::cerr << s - temp << ")" << std::endl;
    // for (int i = l; i <= r; ++i) std::cerr << min[i] << ' ';
    // std::cerr << std::endl;
    // for (int i = l; i <= r; ++i) std::cerr << max[i] << ' ';
    // std::cerr << std::endl;
    solve(l, m), solve(m + 1, r);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> x >> y, a[x] = y;
    solve(1, n);
    std::cout << s << std::endl;
    return 0;
}