#include <bits/stdc++.h>

const int N = 300005;

struct Ptr;

struct Node {
    Ptr s[2], f;
    int key, add, size;
    inline void Add(int x) { add += x, key += x; }
};

Node No[N];

struct Ptr {
    int x;
    inline Ptr(int a = 0) : x(a) {}
    Node *operator->() { return &No[x]; }
    inline operator bool() { return bool(x); }
};

inline int Get(Ptr u) { return u->f->s[1] == u; }

inline int PushUp(Ptr u) { u->size = 1 + u->s[0]->size + u->s[1]->size; }

inline int PushDown(Ptr u) {
    if (u->add) {
        if (u->s[0]) u->s[0]->Add(u->add);
        if (u->s[1]) u->s[1]->Add(u->add);
        u->add = 0;
    }
}

inline void Rotate(Ptr u) {
    int p = Get(u), q = !p;
    PushDown(u->f), PushDown(u);
    if (u->f->s[p] = u->s[q]) u->s[q]->f = u->f;
    if (u->s[q] = u->f, u->f = u->f->f) u->f->s[Get(u->s[q])] = u;
    u->s[q]->f = u, PushUp(u->s[q]), PushUp(u);
}

Ptr Root;

inline void Splay(Ptr u) {
    for (Ptr f; f = u->f; Rotate(u)) {
        if (u->f->f) Rotate(Get(u) == Get(u->f) ? f : u);
    }
    Root = u;
}

int n;

inline Ptr SplayFindGEx(int x) {
    Ptr u = Root, Ans = 0, v = u;
    while (u) {
        PushDown(u);
        if (u->key >= x) Ans = x;
        v = u, u = u->s[u->key < x];
    }
    Splay(v);
    return Ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    int Ans = 1;
    for (int i = 1; i <= n; ++i) {
        int l, r;
        std::cin >> l >> r;
        if (!Root && ((Root = i)->key = l)) continue;
        Ptr u = SplayFindGEx(l);
        if (!u) {
            u = Root, ++Ans;
            while (PushDown(u), u->s[1]) u = u->s[1];
            Splay(u);
            u->s[1] = i, Ptr(i)->f = u, Ptr(i)->key = l;
        } else if (u->key >= r) {
            u->key = l;
        } else {
            Ptr v = SplayFindGEx(r);
            Splay(v), PushDown(v);
            if (v->s[1]) {
                Ptr c = v->s[1];
                PushDown(c);
                while (c->s[0]) PushDown(c = c->s[0]);
                
            }
        }
    }
    return 0;
}