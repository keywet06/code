#include <bits/stdc++.h>
const int N = 50000;
const int Np = N + 5;
long long n, L, Lp, head, tail;
long long a[Np], b[Np], c[Np], f[Np], s[Np];
template <typename _Tp>
  _Tp sqr(_Tp x);
template <typename _Tp>
  _Tp sqr (_Tp x) { return x * x; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> L;
    for (int i = 1; i <= n; ++i) {
        std::cin >> c[i];
        a[i] = a[i - 1] + c[i] + 1;
    }
    Lp = L + 1;
    b[0] = sqr(Lp);
    head = 1;
    tail = 0;
    s[++tail] = 0;
    for (int i = 1; i <= n; ++i) {
        while (head < tail && 1.0 * ((b[s[head + 1]] - b[s[head]]) /
          (a[s[head + 1]] - a[s[head]]) <= 2 * a[i] )) {
            ++head;
        }
        f[i] = f[s[head]] + sqr(a[i] - a[s[head]] - Lp);
        b[i] = f[i] + sqr(a[i] + Lp);
        while (head < tail && 1.0 * (b[i] - b[s[tail]]) / (a[i] - a[s[tail]]) <=
          1.0 * (b[s[tail]] - b[s[tail - 1]]) / (a[s[tail]] - a[s[tail - 1]])) {
            --tail;
        }
        s[++tail] = i;
    }
    std::cout << f[n] << std::endl;
    return 0;
}