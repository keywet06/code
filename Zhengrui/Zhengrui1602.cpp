#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

void ios();

inline void ios() {
    std::ios::sync_with_stdio();
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int N = 100005;
const int64 P = 1000000007;

int64 &m(int64 &x);

int n, q;
int o[N], l[N], r[N];
int64 k;
int64 a[N], b[N];

inline int64 &m(int64 &x) { return x = (x % P + P) % P; }

int main() {
    oct::ios();
    std::cin >> n >> q;
    for (int i = 1; i <= q; ++i) std::cin >> o[i] >> l[i] >> r[i];
    for (int i = q; i; --i) {
        m(k = k + b[i]);
        if (o[i] == 1) a[r[i]] += k + 1, a[l[i] - 1] -= k + 1;
        if (o[i] == 2) b[r[i]] += k + 1, b[l[i] - 1] -= k + 1;
    }
    k = 0;
    for (int i = n; i; --i) a[i] = m(k = k + a[i]);
    for (int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
    return 0;
}