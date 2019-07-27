#include <bits/stdc++.h>
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
            class node {
                public:
                    node* next;
                    int to;
            };
        public:
            typedef node* iterator;
        private:
            std::vector<node> ed;
            iterator cnt;
            std::vector<iterator> head;
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
        cnt = &(ed[0]) - 1;
    }
    inline void Tu::updatehead(int x, Tu::iterator it) {
        if (head.size() <= x) {
            while (head.size() > x) {
                head.push_back(0);
            }
        }
        head[x] = it;
    }
    inline Tu::iterator Tu::gethead(int x) {
        if (head.size() <= x) {
            while (head.size() > x) {
                head.push_back(0);
            }
        }
        return head[x];
    }
    inline void Tu::insert(int x, int y) {
        ed.push_back((node){NULL, 0});
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
}
const int M = 200005;
const int N = 100005;
int CLOCK, m, n, p, r, x, y;
long long z;
int undfn[N];
point p[N];
spoint sp[N];
kw::Tu tu;
void dfs1(int = 1, int = 0);
void dfs2(int = 1, int = 1);
void build(int = 1, int = 1, int = n);
long long fun(int, int);
void update(int = 1, int = 1, int = n);
long long query(int = 1, int  = 1, int = n);
void updateS(int, int);
int main() {
    scanf("%d %d %d %d", &m, &n, &p, &r);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &p[i].val);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        tu.addedge(x, y);
    }
    dfs1();
    dfs2();
    return 0;
}
inline void dfs1(int v, int fa) {
    int max = 0;
    p[v].size = 1;
    p[v].son = 0;
    p[v].fa = fa;
    p[v].deep = p[fa].deep + 1;
    for (kw::Tu::iterator it = tu.gethead(v); it; ++it) {
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
    for (kw::Tu::iterator it = tu.gethead(v); it; ++it) {
        if (it->to == p[v].fa || it->to == p[v].son) {
            continue;
        }
        dfs2(p[v].son, p[v].son);
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
}
inline long long fun(int l, int r) {
    return std::min(y, r) - std::max(x, l) + 1;
}
inline void update(int v, int l, int r) {
    sp[v].sum += fun(l, r) * z;
    sp[v].sum %= p;
    if (x <= l && r <= y) {
        plus += z;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(v << 1, l, mid);
    }
    if (y > mid) {
        update(v << 1 | 1, mid + 1, r);
    }
}
inline long long query(int v, int l, int r) {
    long long tmp = sp[v].plus * fun(l, r) % p;
    if (x <= l && r <= y) {
        return (sp[v].sum + tmp) % p;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        tmp += query(v << 1, l, mid);
    }
    if (y > mid) {
        tmp += query(v << 1 | 1, mid + 1, r);
    }
    return tmp % p;
}
inline void update()