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
const long long C = 20;
const long long INF = 1e16;
const long long M = 600005;
const long long N = 100005;
class node1 {
    public:
        long long x, y, z, w;
};
class node2 {
    public:
        long long size, bson, fa, dfn, up, val, deep;
};
class point {
    public:
        point *lson, *rson;
        long long min, val;
};
class data {
    
};
long long CLOCK, sum, ans, m, n, x, y, z;
long long lg[N], und[N];
long long us[N][C];
node1 a[M];
node2 b[N];
point po[N];
point *cnt = po, *root = po;
kw::DisjointSet<N> ds;
kw::Tu<N, M, long long> Tu;
long long operator < (node1, node1);
void dfs1(long long, long long);
void dfs2(long long, long long);
void update(point*);
long long toup(long long, long long);
void build(point* = root, long long = 1, long long = n);
long long query(long long, long long, point* = root, long long = 1, long long = n);
long long queryS(long long, long long);
void printtree();
int main() {
    scanf("%lld %lld", &n, &m);
    for (long long i = 1; i <= m; ++i) {
        scanf("%lld %lld %lld", &a[i].x, &a[i].y, &a[i].z);
    }
    std::sort(a + 1, a + m + 1);
    for (long long i = 1; i <= m; ++i) {
        if (ds.find(a[i].x) == ds.find(a[i].y)) {
            continue;
        }
        Tu.addedge(a[i].x, a[i].y, a[i].z);
        a[i].w = 1;
        sum += a[i].z;
        ds.merge(a[i].x, a[i].y);
    }
    dfs1(1, 1);
    for (long long i = 1; i <= n; ++i) {
        us[i][0] = b[i].fa;
    }
    dfs2(1, 1);
    build();
    for (long long i = 0; (1 << i) < N; ++i) {
        lg[1 << i] = i;
    }
    ans = INF;
    for (long long i = 1; i <= m; ++i) {
        if (a[i].w) {
            continue;
        }
        long long tmp = queryS(a[i].x, a[i].y);
        if (tmp == a[i].z || tmp == INF) {
            continue;
        }
        ans = std::min(ans, sum + a[i].z - tmp);
    }
    printf("%lld\n", ans);
    return 0;
}
inline long long operator < (node1 a, node1 b) {
    return a.z < b.z;
}
inline void dfs1(long long v, long long fa) {
    b[v].size = 1;
    b[v].fa = fa;
    b[v].deep = b[fa].deep + 1;
    for (kw::Tu<N, M, long long>::iterator it = Tu.GetHead(v); it; it = it->next) {
        if (it->to == fa) {
            continue;
        }
        dfs1(it->to, v);
        b[it->to].val = it->data;
        b[v].size += b[it->to].size;
        if (b[it->to].size > b[b[v].bson].size) {
            b[v].bson = it->to;
        }
    }
}
inline void dfs2(long long v, long long up) {
    b[v].up = up;
    b[v].dfn = ++CLOCK;
    und[CLOCK] = v;
    for (long long i = 1; i < C; ++i) {
        us[v][i] = us[us[v][i - 1]][i - 1];
    }
    if (b[v].bson) {
        dfs2(b[v].bson, up);
    }
    for (kw::Tu<N, M, long long>::iterator it = Tu.GetHead(v); it; it = it->next) {
        if (it->to == b[v].fa || it->to == b[v].bson) {
            continue;
        }
        dfs2(it->to, it->to);
    }
}
inline void update(point *v) {
    v->min = (v->lson ? v->lson->min : INF) + (v->rson ? v->rson->min : INF);
}
inline long long toup(long long v, long long x) {
    for (; x; x -= x & (-x)) {
        v = us[v][lg[x & (-x)]];
    }
    return v;
}
inline void build(point *v, long long l, long long r) {
    if (l == r) {
        v->val = b[und[l]].val;
        v->min = b[und[l]].val;
        return;
    }
    long long mid = (l + r) >> 1;
    build(v->lson = ++cnt, l, mid);
    build(v->rson = ++cnt, mid + 1, r);
    update(v);
}
inline long long query(long long x, long long y, point *v, long long l, long long r) {
    if (x <= l && r <= y) {
        return v->min;
    }
    long long ans = INF, mid = (l + r) >> 1;
    if (x <= mid) {
        ans = std::min(ans, query(x, y, v->lson, l, mid));
    }
    if (y > mid) {
        ans = std::min(ans, query(x, y, v->rson, mid + 1, r));
    }
    return ans;
}
inline long long queryS(long long x, long long y) {
    long long tmp = INF;
    while (b[x].up != b[y].up) {
        if (b[b[x].up].deep < b[b[y].up].deep) {
            std::swap(x, y);
        }
        tmp = std::min(tmp, x != b[x].up ? query(b[b[x].up].dfn, b[x].dfn) : tmp);
        x = b[b[x].up].fa;
    }
    if (b[x].deep > b[y].deep) {
        std::swap(x, y);
    }
    tmp = std::min(tmp, x != y ? query(b[toup(y, b[y].deep - b[x].deep - 1)].dfn, b[y].dfn) : tmp);
    return tmp;
}
inline void printtree() {
    std::queue<long long> queue;
    queue.push(1);
    while (!queue.empty()) {
        long long v = queue.front();
        queue.pop();
        for (kw::Tu<N, M, long long>::iterator it = Tu.GetHead(v); it; it = it->next) {
            if (it->to == b[v].fa) {
                continue;
            }
            queue.push(it->to);
        }
    }
}