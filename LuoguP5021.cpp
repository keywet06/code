#include <bits/stdc++.h>
class edge {
    public:
        edge *next;
        int to, len;
};
const int N = 50005;
const int M = 100005;
edge ed[M];
edge *cnt = ed;
edge *head[N];
int ans, m, mid, n, x, y, z, l, r, vw;
std::multiset<int> t[N];
std::multiset<int>::iterator it;
void insert(int, int, int);
void addedge(int, int, int);
int dp(int, int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        addedge(x, y, z);
        r += z;
    }
    while (l < r) {
        mid = (l + r + 1) >> 1;
        ans = 0;
        dp(1, 1);
        if (ans >= m) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", l);
    return 0;
}
inline void insert(int x, int y, int z) {
    ++cnt;
    cnt->next = head[x];
    head[x] = cnt;
    cnt->to = y;
    cnt->len = z;
}
inline void addedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, z);
}
inline int dp(int v, int fa) {
    int s;
    t[v].clear();
    for (register edge *u = head[v]; u; u = u->next) {
        if (u->to == fa) {
            continue;
        }
        s = dp(u->to, v) + u->len;
        if (s >= mid) {
            ++ans;
        } else {
            t[v].insert(s);
        }
    }
    s = 0;
    while (!t[v].empty()) {
        if (t[v].size() == 1) {
            return std::max(s, *t[v].begin());
        }
        it = t[v].lower_bound(mid - *t[v].begin());
        if (it == t[v].begin() && t[v].count(*it) == 1) {
            ++it;
        }
        if (it == t[v].end()) {
            s = std::max(s, *t[v].begin());
            t[v].erase(t[v].begin());
        } else {
            ++ans;
            t[v].erase(it);
            t[v].erase(t[v].begin());
        }
    }
    return s;
}