#include <bits/stdc++.h>

const int N = 2005;
const int E = N * 3;

int n, Top;
int a[N], Len[N], Oper[E];

inline void Reva(int f) {
    int Sum = 0;
    for (int i = 1; i <= f; ++i) Sum += Len[i];
    Oper[++Top] = Sum;
    for (int i = 1, j = f; i < j; ++i, --j) std::swap(a[i], a[j]), std::swap(Len[i], Len[j]);
    for (int i = 1; i <= f; ++i) a[i] = -a[i];
}

inline int Find(int x) {
    for (int i = 1; i <= n; ++i) {
        if (a[i] == x || a[i] == -x) return i;
    }
    assert(false);
}

inline void Merge(int x, int y) {
    assert(std::abs(a[x] - a[y]) == 1);
    assert(a[x] * a[y] > 0);
    assert(a[x] < a[y]);
    int c = a[x] > 0 ? (Len[x] += Len[y], y) : (Len[y] += Len[x], x);
    int p = std::abs(a[c]);
    --n;
    for (int i = c; i <= n; ++i) a[i] = a[i + 1], Len[i] = Len[i + 1];
    for (int i = 1; i <= n; ++i) a[i] += std::abs(a[i]) > p ? a[i] > 0 ? -1 : 1 : 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    int d = 0;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], Len[i] = 1, d += std::abs(a[i] + i);
    if (d == 0) {
        std::cout << n * 2 << '\n';
        for (int i = 1; i <= n; ++i) std::cout << n - 1 << ' ' << n << " \n"[i == n];
        return 0;
    }
    while (n > 1) {
        int p = std::abs(a[1]), c;
        if (p < n) {
            if (a[c = Find(p + 1)] > 0) {
                if (a[1] > 0) Reva(1);
                Reva(c - 1), Merge(c - 1, c);
                continue;
            } else if (a[1] > 0) {
                Reva(c), Reva(c - 1), Merge(c - 1, c);
                continue;
            }
        }
        if (p > 1) {
            if (a[c = Find(p - 1)] < 0) {
                if (a[1] < 0) Reva(1);
                Reva(c - 1), Merge(c - 1, c);
                continue;
            } else if (a[1] < 0) {
                Reva(c), Reva(c - 1), Merge(c - 1, c);
                continue;
            }
        }
        Reva(1);
    }
    if (a[1] < 0) Reva(1);
    std::cout << Top << '\n';
    for (int i = 1; i <= Top; ++i) std::cout << Oper[i] << " \n"[i == Top];
    return 0;
}