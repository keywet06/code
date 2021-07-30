#include <bits/stdc++.h>

#define fir first
#define sec second

using int64 = long long;

const int B = 2;
const int N = 100005;
const int P = 998244353;

int T, n, x, y, z;
int a[N];

std::map<int, int64> nil, nail;
std::map<int, int64> dp[N][B];

std::vector<int> to[N];

inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

inline void add(int64 &x, int64 y) {
    x = (x + y) % P;
}

inline void dfs(int u, int f) {
    std::vector<std::map<int, int64> > d;
    d.push_back(nail);
    for (int v : to[u]) {
        if (v == f) continue;
        dfs(v, u);
        std::vector<std::map<int, int64> > t(d.size() + 1);
        for (int i = 0; i < d.size(); ++i) {
            for (auto x : d[i]) {
                for (auto y : dp[v][0]) {
                    add(t[i + 1][gcd(x.fir, y.fir)], x.sec * y.sec);
                }
                for (auto y : dp[v][1]) {
                    add(t[i][gcd(x.fir, y.fir)], x.sec * y.sec);
                }
            }
        }
        d = t;
    }
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < d.size(); ++j) {
            for (auto x : d[j]) {
                add(dp[u][i][gcd(x.fir, j + i)], x.sec);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    nail[0] = 1;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n; ++i) {
            to[i].clear(), dp[i][0].clear(), dp[i][1].clear(), a[i] = 0;
        }
        for (int i = 1; i < n; ++i) {
            std::cin >> x >> y;
            to[x].push_back(y);
            to[y].push_back(x);
        }
        dfs(1, 1);
        for (auto x : dp[1][0]) a[x.fir] = x.sec;
        for (int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
        std::cout << std::endl;
    }
    return 0;
}