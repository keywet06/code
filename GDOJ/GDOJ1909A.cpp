#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

#define templ template <typename Type1, typename Type2>
templ inline Type1 Min(Type1 x, Type2 y) { return x < y ? x : y; }
templ inline Type1 Max(Type1 x, Type2 y) { return y < x ? x : y; }
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return y < x ? x : x = y; }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 Min(Type1 x, Type2 y, Args... args) { return Min(Min(x, y), args...); }
templ inline Type1 Max(Type1 x, Type2 y, Args... args) { return Max(Max(x, y), args...); }
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

const int B = 4;
const int C = 1 << B;
const int N = 250005;
const int M = 524288;
const int Q = 20005;
const int BA1 = 1e9 + 1;

int m, n, m2, q;

class Seg;

class SegPtr {
   public:
    int x;
    SegPtr(int cx = 0) : x(cx) {}
    Seg *operator->();
};

inline SegPtr NewPtr();
inline SegPtr NewPtr(SegPtr x);

class Seg {
   public:
    SegPtr ls, rs;
    int Tag[B];
    int Min[C];
    inline Seg() {}
    inline Seg(int *a) {
        Min[0] = 0;
        for (int i = 1; i < m2; ++i) Min[i] = Min[i & (i - 1)] + a[__builtin_ctz(i)];
    }
    inline void Modify(int o, int x, int v) {
        if (o == 1) {
            for (int i = 1; i < m2; ++i) {
                if (i & 1 << x) Min[i] += v;
            }
            Tag[x] = (Tag[x] ? Tag[x] : -BA1) + v;
        } else {
            for (int i = 1; i < m2; ++i) {
                if (i & 1 << x) Min[i] = Min[i ^ 1 << x] + v;
            }
            Tag[x] = BA1 + v;
        }
    }
    inline void PushDown() {
        ls = NewPtr(ls), rs = NewPtr(rs);
        for (int c = 0; c < m; ++c) {
            if (Tag[c] > 0) {
                Tag[c] -= BA1;
                ls->Modify(2, c, Tag[c]);
                rs->Modify(2, c, Tag[c]);
            } else if (Tag[c] < 0) {
                Tag[c] += BA1;
                ls->Modify(1, c, Tag[c]);
                rs->Modify(1, c, Tag[c]);
            }
            Tag[c] = 0;
        }
    }
    inline void PushUp() {
        for (int i = 1; i < m2; ++i) Min[i] = std::min(ls->Min[i], rs->Min[i]);
    }
};

extern SegPtr Root[Q];

inline void PutTree(SegPtr u, int l, int r) {
    Debug << "i : { l = " << l << ", r = " << r << ", Tag = {";
    for (int j = 0, c = 0; j < m; ++j) {
        if (c) Deb << ", ";
        c = 1, Deb << u->Tag[j];
    }
    Deb << "}, Min = {";
    for (int j = 1, c = 0; j < m2; ++j) {
        if (c) Deb << ", ";
        c = 1, Deb << u->Min[j];
    }
    Deb << "} }" << std::endl;
    int Mid = l + r >> 1;
    if (l < r) PutTree(u->ls, l, Mid), PutTree(u->rs, Mid + 1, r);
}

int a[N][B];

inline void Build(SegPtr u, int l, int r) {
    if (l == r) return u->operator=(a[l]), void(0);
    int Mid = l + r >> 1;
    Build(u->ls = NewPtr(), l, Mid);
    Build(u->rs = NewPtr(), Mid + 1, r);
    u->PushUp();
}

inline int Query(SegPtr u, int l, int r, int L, int R) {
    if (l >= L && r <= R) return u->Min[m2 - 1];
    int Midl = l + r >> 1, Ans = INT_MAX;
    u->PushDown();
    if (L <= Midl) Mid(Ans, Query(u->ls, l, Midl, L, R));
    if (R > Midl) Mid(Ans, Query(u->rs, Midl + 1, r, L, R));
    return Ans;
}

inline void Update(SegPtr u, int l, int r, int L, int R, int o, int x, int v) {
    if (l >= L && r <= R) return u->Modify(o, x, v);
    int Mid = l + r >> 1;
    u->PushDown();
    if (L <= Mid) Update(u->ls, l, Mid, L, R, o, x, v);
    if (R > Mid) Update(u->rs, Mid + 1, r, L, R, o, x, v);
    u->PushUp();
}

const int PoorSize = 20 * Q * 4 + M;

int PoorCnt;
Seg Poor[PoorSize];

SegPtr Root[Q];

inline SegPtr NewPtr() { return PoorCnt++; }
inline SegPtr NewPtr(SegPtr x) { return Poor[PoorCnt] = Poor[x.x], PoorCnt++; }

inline Seg *SegPtr::operator->() { return Poor + this->x; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> m >> n >> q, m2 = 1 << m;
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j <= n; ++j) std::cin >> a[j][i];
    }
    Build(Root[0] = NewPtr(), 1, n);
    for (int u = 1, v, o, i, l, r, c; u <= q; ++u) {
        std::cin >> v >> o;
        if (o <= 2) {
            std::cin >> i >> l >> r >> c, --i;
            Update(Root[u] = NewPtr(Root[v]), 1, n, l, r, o, i, c);
        } else {
            std::cin >> l >> r;
            std::cout << Query(Root[u] = NewPtr(Root[v]), 1, n, l, r) << '\n';
        }
    }
    return 0;
}