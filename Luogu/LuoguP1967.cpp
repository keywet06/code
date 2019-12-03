#ifndef KW_DISJOINTSET_HPP
#  define KW_DISJOINTSET_HPP
// Head files
#  ifndef STD_BITS_STDCPP_H
#    define STD_BITS_STDCPP_H
#    include <bits/stdc++.h>
#  endif
// Class Definition
namespace kw {
    template<int PointNum> class DisjointSet;
}
// Class Realization
namespace kw {
    template<int PointNum> class DisjointSet {
        // Variable Definition
        private:
            int fi[PointNum];
        // Function Definition
        public:
            DisjointSet();
            void clear();
            int find(int);
            void merge(int, int);
    };
}
// Function Realization
namespace kw {
    template<int PointNum> inline DisjointSet<PointNum>::DisjointSet() {
        for (int i = 1; i <= PointNum; ++i) {
            fi[i] = i;
        }
    }
    template<int PointNum> inline void DisjointSet<PointNum>::clear() {
        for (int i = 1; i <= PointNum; ++i) {
            fi[i] = i;
        }
    }
    template<int PointNum> inline int DisjointSet<PointNum>::find(int x) {
        return this->fi[x] == x ? x : this->fi[x] = this->find(this->fi[x]);
    }
    template<int PointNum> inline void DisjointSet<PointNum>::merge(int x, int y) {
        x = this->find(x);
        y = this->find(y);
        if (x > y) {
            this->fi[y] = x;
        } else {
            this->fi[x] = y;
        }
    }
}
#endif
#ifndef KW_TU_HPP
#  define KW_TU_HPP
// Head files
#  ifndef STD_BITS_STDCPP_H
#    define STD_BITS_STDCPP_H
#    include <bits/stdc++.h>
#  endif
// Class Definition
namespace kw {
    template<int PointNum, int EdgeNum, typename DataType> class Tu;
}
// Class Realization & Function Definition
namespace kw {
    template<int PointNum, int EdgeNum, typename DataType> class Tu {
        // Class Definition
        private:
            class edge;
        public:
            typedef edge* iterator;
        // Variable Definition
        private:
            edge ed[EdgeNum + 1];
            iterator cnt;
            iterator head[PointNum + 1];
        // Class Realization & Function Definition
        private:
            class edge {
                // Variable Definition
                public:
                    int to;
                    iterator next;
                    DataType data;
            };
        public:
            Tu();
            void clear();
            iterator GetHead(int);
            void insert(int, int, DataType);
            void addedge(int, int, DataType);
            void delinsert(int, int);
            void deledge(int, int);
            void delinsert(int, int, DataType);
            void deledge(int, int, DataType);
            iterator GetIt(int, int);
    };
}
// Function Realization
namespace kw {
    template<int PointNum, int EdgeNum, typename DataType> inline Tu<PointNum, EdgeNum, DataType>::Tu() {
        memset(this->head, 0, sizeof(this->head));
        memset(this->ed, 0, sizeof(this->ed));
        this->cnt = this->ed;
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::clear() {
        memset(this->head, 0, sizeof(this->head));
        memset(this->ed, 0, sizeof(this->ed));
        this->cnt = this->ed;
    }
    template<int PointNum, int EdgeNum, typename DataType> inline typename Tu<PointNum, EdgeNum, DataType>::iterator Tu<PointNum, EdgeNum, DataType>::GetHead(int x) {
        return this->head[x];
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::insert(int x, int y, DataType z) {
        ++this->cnt;
        this->cnt->next = this->head[x];
        this->head[x] = this->cnt;
        this->cnt->to = y;
        this->cnt->data = z;
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::addedge(int x, int y, DataType z) {
        this->insert(x, y, z);
        this->insert(y, x, z);
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::delinsert(int x, int y) {
        while (this->GetHead(x) && this->GetHead(x)->to == y) {
            this->head[x] = this->GetHead(x)->next;
        }
        typename Tu<PointNum, EdgeNum, DataType>::iterator its = this->GetHead(x);
        for (typename Tu<PointNum, EdgeNum, DataType>::iterator it = this->GetHead(x); it;) {
            while (it && it->to == y) {
                its->next = it->next;
                it = it->next;
            }
            its = it;
            if (it) {
                it = it->next;
            }
        }
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::deledge(int x, int y) {
        this->delinsert(x, y);
        this->delinsert(y, x);
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::delinsert(int x, int y, DataType z) {
        while (this->GetHead(x) && this->GetHead(x)->to == y && this->GetHead(x)->data == z) {
            this->head[x] = this->GetHead(x)->next;
        }
        typename Tu<PointNum, EdgeNum, DataType>::iterator its = this->GetHead(x);
        for (typename Tu<PointNum, EdgeNum, DataType>::iterator it = this->GetHead(x); it;) {
            while (it && it->to == y && it->data == z) {
                its->next = it->next;
                it = it->next;
            }
            its = it;
            if (it) {
                it = it->next;
            }
        }
    }
    template<int PointNum, int EdgeNum, typename DataType> inline void Tu<PointNum, EdgeNum, DataType>::deledge(int x, int y, DataType z) {
        this->delinsert(x, y, z);
        this->delinsert(y, x, z);
    }
    template<int PointNum, int EdgeNum, typename DataType> inline typename Tu<PointNum, EdgeNum, DataType>::iterator Tu<PointNum, EdgeNum, DataType>::GetIt(int x, int y) {
        typename Tu<PointNum, EdgeNum, DataType>::iterator it = 0;
        for (it = this->GetHead(x); it; it = it->next) {
            if (it->to == y) {
                return it;
            }
        }
        return it;
    }
}
#endif
const int N = 100005;
int CLOCK, cnt, n, m, q, x, y;
int ea[N], ex[N], ey[N], ez[N], es[N], dfn[N], size[N], son[N], up[N], fa[N], min[N], deep[N], udf[N];
kw::DisjointSet<N> DS;
kw::Tu<N, N, int> Tu;
int cmp(int, int);
void dfs1(int, int);
void dfs2(int, int);
void build(int, int, int);
int query(int, int, int, int, int);
int queryS(int, int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &ex[i], &ey[i], &ez[i]);
        es[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        ea[i] = 1e8;
    }
    std::sort(es + 1, es + m + 1, cmp);
    cnt = n;
    for (int i = 1; i <= m; ++i) {
        if (DS.find(ex[es[i]]) != DS.find(ey[es[i]])) {
            DS.merge(ex[es[i]], ey[es[i]]);
            ++cnt;
            Tu.addedge(ex[es[i]], cnt, 0);
            Tu.addedge(cnt, ey[es[i]], 0);
            ea[cnt] = ez[es[i]];
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        if (size[i]) {
            continue;
        }
        dfs1(i, i);
    }
    for (int i = 1; i <= cnt; ++i) {
        if (dfn[i]) {
            continue;
        }
        dfs2(i, i);
    }
    build(1, 1, cnt);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d %d", &x, &y);
        printf("%d\n", DS.find(x) == DS.find(y) ? queryS(x, y) : -1);
    }
    return 0;
}
inline int cmp(int x, int y) {
    return ez[x] > ez[y];
}
inline void dfs1(int v, int f) {
    fa[v] = f;
    size[v] = 1;
    deep[v] = deep[fa[v]] + 1;
    for (kw::Tu<N, N, int>::iterator it = Tu.GetHead(v); it; it = it->next) {
        if (it->to == fa[v]) {
            continue;
        }
        dfs1(it->to, v);
        size[v] += size[it->to];
        if (size[it->to] > size[son[v]]) {
            son[v] = it->to;
        }
    }
}
inline void dfs2(int v, int p) {
    up[v] = p;
    dfn[v] = ++CLOCK;
    udf[CLOCK] = v;
    if (son[v]) {
        dfs2(son[v], p);
    }
    for (kw::Tu<N, N, int>::iterator it = Tu.GetHead(v); it; it = it->next) {
        if (it->to == fa[v] || it->to == son[v]) {
            continue;
        }
        dfs2(it->to, it->to);
    }
}
inline void build(int v, int l, int r) {
    if (l == r) {
        min[v] = ea[udf[l]];
        return;
    }
    int mid = l + r >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    min[v] = std::min(min[v << 1], min[v << 1 | 1]);
}
inline int query(int v, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return min[v];
    }
    int mid = l + r >> 1, tmp = 1e8;
    if (x <= mid) {
        tmp = std::min(tmp, query(v << 1, l, mid, x, y));
    }
    if (y > mid) {
        tmp = std::min(tmp, query(v << 1 | 1, mid + 1, r, x, y));
    }
    return tmp;
}
inline int queryS(int x, int y) {
    int tmp = 1e8;
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        tmp = std::min(tmp, query(1, 1, cnt, dfn[up[x]], dfn[x]));
        x = fa[up[x]];
    }
    return std::min(tmp, dfn[x] < dfn[y] ? query(1, 1, cnt, dfn[x], dfn[y]) : query(1, 1, cnt, dfn[y], dfn[x]));
}
