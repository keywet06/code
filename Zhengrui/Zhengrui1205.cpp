#include <bits/stdc++.h>
const int N = 100000;
const int Np = N + 5;
class node;
class node {
   public:
    int a[2];
    long long l, r;
    friend node operator+(node x, int y);
    friend node operator+(node x, node y);
};
void tans(node x);
int a[Np];
long long n, max, min = 0x7fffffff;
node now;
node pre[Np];
inline node operator+(node x, int y) {
    if (x.r == -1) return x;
    int t = x.a[0] % 3;
    if (t > y) return x.r = -1, x;
    x.l += t, x.r += t;
    t = std::min({x.a[0] -= t, x.a[1] -= t, y -= t}) / 3 * 3;
    if (x.a[1] % 3 > y - t && (t -= 3) < 0) return x.r = -1, x;
    return x.a[0] = x.a[1] - t, x.a[1] = y - t, x.r += t, x;
}
inline node operator+(node x, node y) {
    return y.r != -1
               ? (x.r != -1 ? x.l += y.l, x.r += y.r, x + y.a[1] + y.a[0] : x)
               : y;
}
inline void tans(node x) {
    ~x.r ? (max = std::max(max, x.r), min = std::min(min, x.l)) : 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    for (int i = n; i; --i) {
        tans(pre[i - 1] + (a[i] - 2) + now + 0 + 0);
        now = now + a[i];
    }
    std::cout << (max >= min ? (max - min) / 3 + 1 : 0) << std::endl;
    return 0;
}