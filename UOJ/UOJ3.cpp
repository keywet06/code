#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

#define templ template <typename Type1, typename Type2>
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : (x = y); }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return x > y ? x : (x = y); }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

const int N = int(5e5) + 5;
const int M = int(1e6) + 5;
const int Z = N + M;

struct Node {
    int Idb, aMax;
    Node() : Idb(0) {}
    Node(int b, int a) : Idb(b), aMax(a) {}
};

struct Edge {
    int u, v, a, b;
};

int n, m;
int Fa[Z], Son[Z][2], Rev[Z], Pa[Z], Pb[Z];

Node Val[Z], Data[Z];

Edge Ed[Z];

inline Node operator+(Node a, Node b) {
    return Node((Pb[a.Idb] == Pb[b.Idb] ? Pa[a.Idb] > Pa[b.Idb] : Pb[a.Idb] > Pb[b.Idb]) ? a.Idb : b.Idb,
                std::max(a.aMax, b.aMax));
}

inline void PushUp(int u) { Data[u] = Val[u] + Data[Son[u][0]] + Data[Son[u][1]]; }

inline void Reverse(int u) {
    if (u) Rev[u] ^= 1, std::swap(Son[u][0], Son[u][1]), PushUp(u);
}

inline void PushDown(int u) {
    if (Rev[u]) Rev[u] = 0, Reverse(Son[u][0]), Reverse(Son[u][1]);
}

inline int Get(int u) { return Son[Fa[u]][0] == u ? 0 : (Son[Fa[u]][1] == u ? 1 : -1); }

inline void Rotate(int u) {
    int p = Get(u), q = !p, c = Get(Fa[u]);
    if (Son[Fa[u]][p] = Son[u][q]) Fa[Son[u][q]] = u;
    if (c != -1) Son[Fa[Fa[u]]][c] = u;
    Son[u][q] = Fa[u], Fa[u] = Fa[Fa[u]], Fa[Son[u][q]] = u;
    PushUp(Son[u][q]), PushUp(u);
}

inline void UpPushDown(int u) {
    if (Fa[u]) UpPushDown(Fa[u]);
    PushDown(u);
}

inline void Splay(int u) {
    UpPushDown(u);
    for (int f, gu, gfu; f = Fa[u], gu = Get(u), gu != -1; Rotate(u)) {
        if ((gfu = Get(f)) == -1) Rotate(gfu == gu ? f : u);
    }
}

inline int Access(int u) {
    int p;
    for (p = 0; u; p = u, u = Fa[u]) Splay(u), Son[u][1] = p, PushUp(u);
    return p;
}

inline void MakeRoot(int u) { u = Access(u), Reverse(u); }
inline void Link(int u, int v) { MakeRoot(u), Splay(u), Fa[u] = v; }
inline void Cut(int u, int v) { MakeRoot(u), Access(v), Splay(v), Son[v][0] = Fa[u] = 0; }
inline int Split(int u, int v) { return MakeRoot(u), Access(v); }

inline bool SafeCut(int u, int v) {
    MakeRoot(u), Access(v), Splay(v);
    return Son[v][0] == u && !Son[u][1] ? Son[v][0] = Fa[u] = 0, true : false;
}

inline int SafeSplit(int u, int v) {
    Debug << "SafeSplit(" << u << ", " << v << ")" << std::endl;
    MakeRoot(u), Access(v), Splay(u);
    int p = v;
    while (Fa[p]) p = Fa[p];
    Splay(v);
    return p == u ? v : 0;
}

inline void PrintTree() {
    Debug << "PrintTree: " << std::endl;
    for (int i = 1; i <= n + m; ++i) {
        std::cout << "Node[" << i << "] = { Fa: " << Fa[i] << ", "
                  << "Son: (" << Son[i][0] << ", " << Son[i][1] << "), Rev: " << Rev[i] << ", Cost: { a: " << Pa[i]
                  << ", b: " << Pb[i] << " } }" << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) std::cin >> Ed[i].u >> Ed[i].v >> Ed[i].a >> Ed[i].b;
    std::sort(Ed + 1, Ed + m + 1, [](Edge a, Edge b) { return a.a == b.a ? a.b < b.b : a.a < b.a; });
    int Ans = INT_MAX;
    for (int i = 1; i <= m; ++i) {
        PrintTree();
        Pa[n + i] = Ed[i].a, Pb[n + i] = Ed[i].b;
        Val[n + i] = Node(n + i, Ed[i].a);
        Link(Ed[i].v, n + i);
        int x = SafeSplit(Ed[i].u, n + i);
        if (x) x = Data[x].Idb, Cut(x - n, Ed[x - n].u), Cut(x - n, Ed[x - n].v);
        Link(Ed[i].u, n + i);
        if (x = SafeSplit(1, n)) Mid(Ans, Data[x].aMax + Pb[Data[x].Idb]);
    }
    std::cout << Ans << std::endl;
    return 0;
}
