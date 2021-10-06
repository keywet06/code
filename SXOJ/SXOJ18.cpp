#include <bits/stdc++.h>

using pair = std::pair<int, int>;

const int N = 500005;
const int C = 25;
const int D = C << 1;

int n, k, c, cnt, f, o, cnt1, cnt2;
int pa[N], pb[N], head1[N], next1[N], num1[N], head2[N], next2[N], num2[N];
int a[N][D], v[N][D];

std::string s;

std::vector<int> r[N];

std::mt19937 rd(std::chrono::system_clock::now().time_since_epoch().count());

inline int ret() {
    for (int i = 1; i <= n; ++i) r[i].clear();
    for (int i = 1; i <= n; ++i) r[v[i][c]].push_back(i);
    for (int i = 1; i <= n; ++i) {
        for (int x : r[i]) std::cout << x << ' ';
    }
    std::cout << '\n';
    return 0;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> s;
    if (s.length() > 8) {
        k = n << 1;
    } else {
        for (char ch : s) k = k * 10 + ch - '0';
        k = std::min(k, n << 1);
    }
    // for (int i = 1; i <= n; ++i) a[i][0] = rd() % n + 1;
    // for (int i = 1; i <= n; ++i) v[i][0] = rd() % n + 1;
    for (int i = 1; i <= n; ++i) std::cin >> a[i][0];
    for (int i = 1; i <= n; ++i) std::cin >> v[i][0];
    for (c = 1; 1 << c <= k; ++c) {
        cnt1 = cnt2 = 0;
        for (int i = 1; i <= n; ++i) a[i][c] = a[a[i][c - 1]][c - 1];
        for (int i = 1; i <= n; ++i) head1[i] = head2[i] = 0;
        for (int i = 1; i <= n; ++i) {
            pa[i] = v[i][c - 1], pb[i] = v[a[i][c - 1]][c - 1];
            next1[++cnt1] = head1[pb[i]], head1[pb[i]] = cnt1, num1[cnt1] = i;
        }
        for (int i = 1; i <= n; ++i) {
            for (int e = head1[i], x; x = num1[e], e; e = next1[e]) {
                next2[++cnt2] = head2[pa[x]], head2[pa[x]] = cnt2;
                num2[cnt2] = x;
            }
        }
        cnt = 0;
        for (int i = 1; i <= n; ++i) {
            f = -1;
            for (int e = head2[i], x; x = num2[e], e; e = next2[e]) {
                cnt += f != pb[x], f = pb[x], v[x][c] = cnt;
            }
        }
        if (cnt == n) return ret();
    }
    o = c - 1, cnt1 = cnt2 = 0;
    for (int i = 1; i <= n; ++i) a[i][c] = i;
    for (int e = c - 2; ~e; --e) {
        if (!((1 << e) & k)) continue;
        for (int i = 1; i <= n; ++i) a[i][c + 1] = a[a[i][c]][e];
        ++c;
    }
    for (int i = 1; i <= n; ++i) head1[i] = head2[i] = 0;
    for (int i = 1; i <= n; ++i) {
        pa[i] = v[i][o], pb[i] = v[a[i][c]][o];
        next1[++cnt1] = head1[pb[i]], head1[pb[i]] = cnt1, num1[cnt1] = i;
    }
    for (int i = 1; i <= n; ++i) {
        for (int e = head1[i], x; x = num1[e], e; e = next1[e]) {
            next2[++cnt2] = head2[pa[x]], head2[pa[x]] = cnt2;
            num2[cnt2] = x;
        }
    }
    cnt = 0, ++c;
    for (int i = 1; i <= n; ++i) {
        f = -1;
        for (int e = head2[i], x; x = num2[e], e; e = next2[e]) {
            cnt += f != pb[x], f = pb[x], v[x][c] = cnt;
        }
    }
    return ret();
}