#include <bits/stdc++.h>
template <typename T>
void setmin(T& a, T b) {
    if (b < a) a = b;
}
int n;
long long X;
std::vector<int> P;
namespace inversion {
std::vector<int> bit;
long long total;
int num;
void init() {
    bit.resize(n + 1);
    total = 0;
    num = 0;
}
void upd(int i, int d) {
    for (int a = i + 1; a <= n; a += (a & -a)) {
        bit[a] += d;
    }
}
int query(int i) {
    int r = 0;
    for (int a = i; a > 0; a -= (a & -a)) {
        r += bit[a];
    }
    return r;
}
void push_back(int x) {
    total += num - query(x);
    upd(x, 1);
    num++;
}
void pop_back(int x) {
    total -= (num - 1) - query(x);
    upd(x, -1);
    num--;
}
void push_front(int x) {
    total += query(x);
    upd(x, 1);
    num++;
}
void pop_front(int x) {
    total -= query(x);
    upd(x, -1);
    num--;
}
}  // namespace inversion
std::vector<long long> dp;
int li = 0, ri = 0;
void fix(int li1, int ri1) {
    while (li1 < li) {
        inversion::push_front(P[--li]);
    }
    while (ri < ri1) {
        inversion::push_back(P[ri++]);
    }
    while (li1 > li) {
        inversion::pop_front(P[li++]);
    }
    while (ri > ri1) {
        inversion::pop_back(P[--ri]);
    }
}
void trans(int l, int r, int bestl, int bestr) {
    if (l > r) return;
    int x = (l + r) / 2;
    long long best = 1e18;
    int bestj = -1;
    for (int j = bestl; j <= bestr && j < x; j++) {
        fix(j, x);
        long long cnd = dp[j] + X + inversion::total;
        if (cnd < best) {
            best = cnd;
            bestj = j;
        }
    }
    setmin(dp[x], best);
    trans(l, x - 1, bestl, bestj);
    trans(x + 1, r, bestj, bestr);
}
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    solve(l, mid);
    trans(mid + 1, r, l, mid);
    solve(mid + 1, r);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> X;
    P.resize(n);
    for (int i = 0; i < n; i++) {
        std::cin >> P[i];
        P[i]--;
    }
    dp.assign(n + 1, 1e18);
    dp[0] = 0;
    inversion::init();
    solve(0, n);
    std::cout << dp.back() << '\n';
    return 0;
}