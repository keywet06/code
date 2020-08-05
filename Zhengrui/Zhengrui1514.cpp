#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int B = 2;
const int C = 60;
const int P = 150000005;
const int N = 500005;
class point {
   public:
    int size;
    int a[B];
    inline int &operator[](int x) { return a[x]; }
};
class node {
   public:
    int l1, l2, r1, r2;
    long long ans;
    node() {}
    node(int L1, int L2, int R1, int R2, long long A)
        : l1(L1), r1(R1), l2(L2), r2(R2), ans(A) {}
};
int cnt, n;
int a[N], fa[N], size[N], root[N];
long long x;
point p[P];
inline int insert(int u, long long x) {
    int now;
    p[now = ++cnt] = p[u];
    u = cnt;
    ++p[now].size;
    for (int i = C - 1; ~i; --i) {
        p[++cnt] = p[p[now][x >> i & 1]];
        ++p[cnt].size;
        p[now][x >> i & 1] = cnt;
        now = cnt;
    }
    return u;
}
inline int merge(int u1, int u2) {
    int u = ++cnt;
    p[u][0] =
        p[u1][0] && p[u2][0] ? merge(p[u1][0], p[u2][0]) : p[u1][0] + p[u2][0];
    p[u][1] =
        p[u1][1] && p[u2][1] ? merge(p[u1][1], p[u2][1]) : p[u1][1] + p[u2][1];
    p[p[u][0]].size = p[p[u1][0]].size + p[p[u2][0]].size;
    p[p[u][1]].size = p[p[u1][1]].size + p[p[u2][1]].size;
    return u;
}
inline long long solve(int u1, int u2) {
    int flag;
    long long ans[C + 1];
    node u;
    std::queue<node> q[C + 1];
    memset(ans, 0, sizeof(ans));
    q[C].push(node(u1, u2, u1, u2, 0));
    for (int i = C - 1; ~i; --i) {
        while (q[i + 1].size()) {
            u = q[i + 1].front();
            q[i + 1].pop();
            if (u.ans < ans[i + 1]) continue;
            flag = 0;
            if (p[p[u.l1][0]].size - p[p[u.l2][0]].size &&
                p[p[u.r1][1]].size - p[p[u.r2][1]].size) {
                q[i].push(node(p[u.l1][0], p[u.l2][0], p[u.r1][1], p[u.r2][1],
                               u.ans | 1ll << i));
                ans[i] = std::max(ans[i], u.ans | 1ll << i);
                flag = 1;
            }
            if (p[p[u.l1][1]].size - p[p[u.l2][1]].size &&
                p[p[u.r1][0]].size - p[p[u.r2][0]].size && u.l1 != u.r1) {
                q[i].push(node(p[u.l1][1], p[u.l2][1], p[u.r1][0], p[u.r2][0],
                               u.ans | 1ll << i));
                ans[i] = std::max(ans[i], u.ans | 1ll << i);
                flag = 1;
            }
            if (p[p[u.l1][0]].size - p[p[u.l2][0]].size &&
                p[p[u.r1][0]].size - p[p[u.r2][0]].size && !flag) {
                q[i].push(node(p[u.l1][0], p[u.l2][0], p[u.r1][0], p[u.r2][0],
                               u.ans));
                ans[i] = std::max(ans[i], u.ans);
            }
            if (p[p[u.l1][1]].size - p[p[u.l2][1]].size &&
                p[p[u.r1][1]].size - p[p[u.r2][1]].size && !flag) {
                q[i].push(node(p[u.l1][1], p[u.l2][1], p[u.r1][1], p[u.r2][1],
                               u.ans));
                ans[i] = std::max(ans[i], u.ans);
            }
        }
    }
    return ans[0];
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 2; i <= n; ++i) std::cin >> fa[i];
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        root[i] = insert(0, x);
    }
    for (int i = n; i; --i) {
        ++size[i];
        size[fa[i]] += size[i];
        root[fa[i]] = merge(root[fa[i]], root[i]);
        p[root[fa[i]]].size += p[root[i]].size;
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << (size[i] < n - 1 ? solve(root[1], root[i]) : 0)
                  << std::endl;
    }
    return 0;
}