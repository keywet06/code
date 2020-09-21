#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define debug std::cerr << "Debug(" << __LINE__ << "): "
#define pub push_back
#define pob pop_back
#define mkp make_pair
#define fir first
#define sec second

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using pi32 = std::pair<int32, int32>;

namespace oct {

const int tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                       {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

void sync();
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);
template <typename _Tp>
bool in(_Tp x, _Tp l, _Tp r);
template <typename _Tp>
_Tp sqr(_Tp x);

inline void sync() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}
template <typename _Tp>
inline _Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}
template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}
template <typename _Tp>
inline bool in(_Tp x, _Tp l, _Tp r) {
    return l <= x && x <= r;
}
template <typename _Tp>
inline _Tp sqr(_Tp x) {
    return x * x;
}

}  // namespace oct

// the pre-document end

const int N = 1000005;
const int M = 2000005;
int q, n, cnt, ps, pt, flag, count;
int b[N], c[N], head[N], p[N], r[N];
int f[M], s[M], dig[M], size[M], used[M], next[M], to[M];
std::map<int, int> map;
std::stack<int> stack;

inline int find(int x) { return f[x] == x ? f[x] : f[x] = find(f[x]); }
inline int merge(int x, int y) {
    return (x = find(x)) == (y = find(y)) ? x
                                          : (size[x] += size[y], f[y] = f[x]);
}
inline void finished() {
    std::cout << -1 << std::endl;
    exit(0);
}
inline void insert(int u, int v) {
    next[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}
inline void addedge(int u, int v) {
    insert(u, v);
    insert(v, u);
}
inline void dfs(int u, int &t) {
    if (flag && u == t) return;
    flag = 1;
    stack.push(u);
    for (int &e = head[u]; e; e = next[e]) {
        if (used[e]) continue;
        used[e] = used[e ^ 1] = 1;
        dfs(to[e], t);
        e = next[e];
        break;
    }
}
inline int check(int u) {
    for (int &e = head[u]; e; e = next[e]) {
        if (used[e]) continue;
        return 1;
    }
    return 0;
}

int main() {
    oct::sync();
    std::cin >> n;
    for (int i = 1; i < n; ++i) std::cin >> b[i], s[cnt++] = b[i];
    for (int i = 1; i < n; ++i) std::cin >> c[i], s[cnt++] = c[i];
    for (int i = 1; i < n; ++i) {
        if (b[i] > c[i]) finished();
    }
    std::sort(s, s + cnt);
    cnt = std::unique(s, s + cnt) - s;
    for (int i = 0; i < cnt; ++i) map[s[i]] = f[i] = i, size[i] = 1;
    for (int i = 1; i < n; ++i) ++dig[b[i] = map[b[i]]];
    for (int i = 1; i < n; ++i) ++dig[c[i] = map[c[i]]];
    for (int i = 0; i < cnt; ++i) {
        if (!(dig[i] & 1)) continue;
        ++q;
        std::swap(ps, pt);
        ps = i;
    }
    if (q && q != 2) finished();
    for (int i = 1; i < n; ++i) merge(b[i], c[i]);
    if (size[find(0)] < cnt) finished();
    cnt = 1;
    for (int i = 1; i < n; ++i) addedge(b[i], c[i]);
    cnt = flag = 0;
    dfs(ps, pt);
    stack.push(pt);
    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();
        std::cout << s[u] << ' ';
        while (check(u)) flag = 0, dfs(u, u);
    }
    std::cout << std::endl;
    return 0;
}
