#include <bits/stdc++.h>

const int C = 30;
const int N = 100005;

int n, m, f, o;
int a[N], b[N], id[N], u0[N], u1[N];

long long ans;

inline int cmp(int x, int y) { return a[x] < a[y]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) std::cin >> a[i] >> b[i], id[i] = i;
    std::sort(id + 1, id + m + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        if (id[i] != 1 && a[id[i]] != a[id[i - 1]] + 1) f = 1;
        if (!f) {
            ans += (o ^= b[id[i]]);
            continue;
        }
        if (a[id[i]] != a[id[i - 1]] + 1) {
            for (int j = 0; j <= 30; ++j) {
                ans += (1 << j) * std::min(u0[j], u1[j]);
                u0[j] = 1, u1[j] = 0;
            }
            o = 0;
        }
        o ^= b[id[i]];
        for (int j = 0; j <= 30; ++j) {
            if (o & (1 << j)) {
                ++u1[j];
            } else {
                ++u0[j];
            }
        }
    }
    for (int i = 0; i <= 30; ++i) {
        ans += (1 << i) * std::min(u0[i], u1[i]);
        u0[i] = u1[i] = 0;
    }
    std::cout << ans << std::endl;
    return 0;
}