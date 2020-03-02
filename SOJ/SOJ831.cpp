#include <bits/stdc++.h>
const int C = 10;
const int Cp = C + 2;
const int N = 200000;
const int Np = N + 5;
int n, m, l, r, L, R, subtask, k, s;
int a[Np];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    subtask = 3;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (a[i] > 10) {
            subtask = 0;
        }
    }
    if (!subtask || 1ll * n * m <= 1600000000ll) {
        subtask = 2;
    }
    if (subtask == 2) {
        register int i;
        while (m--) {
            std::cin >> l >> r >> L >> R;
            k = s = 0;
            for (i = l; i <= r; ++i) {
                s += k;
                k = L <= a[i] && a[i] <= R ? k + 1 : 0;
            }
            s += k;
            std::cout << s << "\n";
        }
    }
    return 0;
}