#include <bits/stdc++.h>
const int M = 400005;
const int N = 400005;
// $file "kw/tu.hpp"
#ifndef KW_TU_HPP
#define KW_TU_HPP
// Include:
namespace kw {
    #include <bits/stdc++.h>
}
// Declare:
namespace kw {
    class Tu {
        private:
            class edge {
                public:
                    edge *next;
                    int to;
            };
        public:
            typedef edge* iterator;
        private:
            iterator cnt;
            edge ed[M];
            iterator head[N];
            void updatehead(int, iterator);
        public:
            Tu();
            iterator gethead(int);
            void insert(int, int);
            void addedge(int, int);
    };
}
// Implementation:
namespace kw {
    inline Tu::Tu() {
        cnt = ed;
    }
    inline void Tu::updatehead(int x, Tu::iterator it) {
        head[x] = it;
    }
    inline Tu::iterator Tu::gethead(int x) {
        return head[x];
    }
    inline void Tu::insert(int x, int y) {
        ++cnt;
        cnt->next = gethead(x);
        updatehead(x, cnt);
        cnt->to = y;
    }
    inline void Tu::addedge(int x, int y) {
        insert(x, y);
        insert(y, x);
    }
}
#endif
// $endfile
struct point {
    public:
        int size, son, dfn, up, fa, tend, val, deep;
};
struct spoint {
    public:
        long long sum, plus;
};
int CLOCK, m, n, mod, r, x, y;
long long z;
int undfn[N];
point p[N];
spoint sp[N];
kw::Tu tu;
void dfs1(int = r, int = 0);
void dfs2(int = r, int = r);
void build(int = 1, int = 1, int = n);
long long fun(int, int, int, int);
void update(int, int, int, int = 1, int = 1, int = n);
long long query(int, int, int = 1, int = 1, int = n);
void updateS(int, int, int);
long long queryS(int, int);
int main() {
    scanf("%d %d %d %d", &n, &m, &r, &mod);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &p[i].val);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        tu.addedge(x, y);
    }
    dfs1();
    dfs2();
    build();
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &x);
        if (x == 1) {
            scanf("%d %d %lld", &x, &y, &z);
            updateS(x, y, z);
        } else if (x == 2) {
            scanf("%d %d", &x, &y);
            printf("%lld\n", queryS(x, y));
        } else if (x == 3) {
            scanf("%d %lld", &x, &z);
            update(p[x].dfn, p[x].tend, z);
        } else {
            scanf("%d", &x);
            printf("%lld\n", query(p[x].dfn, p[x].tend));
        }
    }
    return 0;
}
inline void dfs1(int v, int fa) {
    int max = 0;
    p[v].size = 1;
    p[v].son = 0;
    p[v].fa = fa;
    p[v].deep = p[fa].deep + 1;
    for (kw::Tu::iterator it = tu.gethead(v); it; it = it->next) {
        if (it->to == fa) {
            continue;
        }
        dfs1(it->to, v);
        p[v].size += p[it->to].size;
        if (p[it->to].size > max) {
            max = p[it->to].size;
            p[v].son = it->to;
        }
    }
}
inline void dfs2(int v, int up) {
    p[v].up = up;
    p[v].dfn = ++CLOCK;
    undfn[CLOCK] = v;
    if (!p[v].son) {
        p[v].tend = CLOCK;
        return;
    }
    dfs2(p[v].son, up);
    for (kw::Tu::iterator it = tu.gethead(v); it; it = it->next) {
        if (it->to == p[v].fa || it->to == p[v].son) {
            continue;
        }
        dfs2(it->to, it->to);
    }
    p[v].tend = CLOCK;
}
inline void build(int v, int l, int r) {
    if (l == r) {
        sp[v].sum = p[undfn[l]].val;
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    sp[v].sum = sp[v << 1].sum + sp[v << 1 | 1].sum;
    sp[v].sum %= mod;
}
inline long long fun(int x, int y, int l, int r) {
    return std::min(y, r) - std::max(x, l) + 1;
}
inline void update(int x, int y, int z, int v, int l, int r) {
    sp[v].sum += fun(x, y, l, r) * z;
    sp[v].sum %= mod;
    if (x <= l && r <= y) {
        sp[v].plus += z;
        sp[v].plus %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(x, y, z, v << 1, l, mid);
    }
    if (y > mid) {
        update(x, y, z, v << 1 | 1, mid + 1, r);
    }
}
inline long long query(int x, int y, int v, int l, int r) {
    if (x <= l && r <= y) {
        return sp[v].sum;
    }
    long long tmp = sp[v].plus * fun(x, y, l, r) % mod;
    int mid = (l + r) >> 1;
    if (x <= mid) {
        tmp += query(x, y, v << 1, l, mid);
    }
    if (y > mid) {
        tmp += query(x, y, v << 1 | 1, mid + 1, r);
    }
    return tmp % mod;
}
inline void updateS(int x, int y, int z) {
    while (p[x].up != p[y].up) {
        if (p[p[x].up].deep < p[p[y].up].deep) {
            std::swap(x, y);
        }
        update(p[p[x].up].dfn, p[x].dfn, z);
        x = p[p[x].up].fa;
    }
    if (p[x].dfn > p[y].dfn) {
        std::swap(x, y);
    }
    update(p[x].dfn, p[y].dfn, z);
}
inline long long queryS(int x, int y) {
    long long tmp = 0;
    while (p[x].up != p[y].up) {
        if (p[p[x].up].deep < p[p[y].up].deep) {
            std::swap(x, y);
        }
        tmp += query(p[x].dfn, p[p[x].up].dfn);
        tmp %= mod;
        x = p[p[x].up].fa;
    }
    if (p[x].dfn > p[y].dfn) {
        std::swap(x, y);
    }
    tmp += query(p[x].dfn, p[y].dfn);
    return tmp % mod;
}
