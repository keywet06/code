#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

const int N = 200005;

struct MonStaNode {
    int l, r, v;
    MonStaNode(int cl = 0, int cr = 0, int cv = 0) : l(cl), r(cr), v(cv) {}
};

struct Sta {
    int Cnt;
    MonStaNode s[N];
    Sta() : Cnt(0) {}
    size_t size() { return Cnt; }
    void push_back(MonStaNode x) { s[++Cnt] = std::move(x); }
    template <typename... Args>
    void emplace_back(Args... args) {
        s[++Cnt] = MonStaNode(args...);
    }
    MonStaNode &operator[](size_t i) { return s[i]; }
    MonStaNode &top(int i = 0) { return s[Cnt - i]; }
    void pop() { --Cnt; }
    void clear() { Cnt = 0; }
};

const int M = 1 << 33 - __builtin_clz(N - 1);

int n, a;

Sta Si, Sa, S1, S2, *Sg = &S1, *St = &S2;

struct Data {
    int64 Min;
    int Num;
    Data(int64 cMin = 0, int cNum = 0) : Min(cMin), Num(cNum) {}
};

/**
 * Segment Tree maintains min & num of t_i, seg add, seg query, seg add i * v.
 * We should found Max - Min = (r - l) * gcd(Max - Min + l * gcd = r * gcd),
 * and we know Max - Min >= (r - l) * gcd(Max - Min + l * gcd >= r * gcd),
 * therefore t_i = Max - Min + l * gcd,
 * and we should maintain the mininum t_i and the number of it.
 */
Data GData[M];
int GAdd[M];

inline Data operator+(Data a, Data b) { return a.Min == b.Min ? Data(a.Min, a.Num + b.Num) : a.Min < b.Min ? a : b; }

inline void PushUp(int u) { GData[u] = GData[u << 1] + GData[u << 1 | 1]; }

inline void PushDown(int u) {
    if (GAdd[u]) {
        GAdd[u << 1 | 1] += GAdd[u], GData[u << 1 | 1].Min += GAdd[u];
        GAdd[u << 1] += GAdd[u], GData[u << 1].Min += GAdd[u], GAdd[u] = 0;
    }
}

// inline std::string C(int l, int r) { return l == 1 && r == n ? "|_________Begin_________|: " : ""; }

inline void Build(int u, int l, int r) {
    if (l == r) return void(GData[u].Num = 1);
    int Mid = l + r >> 1;
    Build(u << 1, l, Mid), Build(u << 1 | 1, Mid + 1, r);
    PushUp(u);
}

inline Data Query(int u, int l, int r, int x, int y) {
    // Debug << C(l, r) << "Query(" << u << ", " << l << ", " << r << ", " << x << ", " << y << ")" << std::endl;
    if (l >= x && r <= y) return GData[u];
    int Mid = l + r >> 1;
    PushDown(u);
    if (y <= Mid) return Query(u << 1, l, Mid, x, y);
    if (x > Mid) return Query(u << 1 | 1, Mid + 1, r, x, y);
    return Query(u << 1, l, Mid, x, y) + Query(u << 1 | 1, Mid + 1, r, x, y);
    // Data Ans;
    // if (y <= Mid) {
    //     Ans = Query(u << 1, l, Mid, x, y);
    // } else if (x > Mid) {
    //     Ans = Query(u << 1 | 1, Mid + 1, r, x, y);
    // } else {
    //     Ans = Query(u << 1, l, Mid, x, y) + Query(u << 1 | 1, Mid + 1, r, x, y);
    // }
    // Debug << C(l, r) << "Query(" << u << ", " << l << ", " << r << ", " << x << ", " << y << ") = (" << Ans.Min << ", " << Ans.Num << ")" << std::endl;
    // return Ans;
}

inline void SegAdd(int u, int l, int r, int x, int y, int c) {
    // Debug << C(l, r) << "SegAdd(" << u << ", " << l << ", " << r << ", " << x << ", " << y << ", " << c << ")"
    //       << std::endl;
    if (l >= x && r <= y) return void((GAdd[u] += c, GData[u].Min += c));
    int Mid = l + r >> 1;
    PushDown(u);
    if (x <= Mid) SegAdd(u << 1, l, Mid, x, y, c);
    if (y > Mid) SegAdd(u << 1 | 1, Mid + 1, r, x, y, c);
    PushUp(u);
}

inline void SegGAdd(int u, int l, int r, int x, int y, int g) {
    // Debug << C(l, r) << "SegGAdd(" << u << ", " << l << ", " << r << ", " << x << ", " << y << ", " << g << ")"
    //       << std::endl;
    if (l == r) return void((GData[u].Min += int64(g) * l));
    int Mid = l + r >> 1;
    PushDown(u);
    if (x <= Mid) SegGAdd(u << 1, l, Mid, x, y, g);
    if (y > Mid) SegGAdd(u << 1 | 1, Mid + 1, r, x, y, g);
    PushUp(u);
}

inline void AddSt(int l, int r, int g) {
    // Debug << C(1, n) << "AddSt(" << l << ", " << r << ", " << g << ")" << std::endl;
    St->size() && St->top().v == g ? void(St->top().r = r) : St->emplace_back(l, r, g);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n, Build(1, 1, n);
    int64 Ans = 0;
    for (int i = 1, g, l; i <= n; ++i) {
        l = a, std::cin >> a, St->clear(), g = std::abs(a - l);
        while (Sa.size() && a > Sa.top().v) SegAdd(1, 1, n, Sa.top().l, Sa.top().r, a - Sa.top().v), Sa.pop();
        Sa.emplace_back(Sa.size() ? Sa.top().r + 1 : 1, i, a);
        while (Si.size() && a < Si.top().v) SegAdd(1, 1, n, Si.top().l, Si.top().r, Si.top().v - a), Si.pop();
        Si.emplace_back(Si.size() ? Si.top().r + 1 : 1, i, a);
        for (int j = 1; j <= Sg->Cnt; ++j) {
            int Newg = std::__gcd(Sg->s[j].v, g);
            if (Newg != Sg->s[j].v) SegGAdd(1, 1, n, Sg->s[j].l, Sg->s[j].r, Newg - Sg->s[j].v);
            AddSt(Sg->s[j].l, Sg->s[j].r, Newg);
            auto q = Query(1, 1, n, Sg->s[j].l, Sg->s[j].r);
            Ans += q.Min == int64(Newg) * i ? q.Num : 0;
        }
        ++Ans, AddSt(i, i, 0), std::swap(St, Sg), std::cout << Ans << " \n"[i == n];
        // Debug << "Sa = [";
        // for (int i = 1; i <= Sa.Cnt; ++i) {
        //     if (i > 1) Deb << ", ";
        //     Deb << "([" << Sa[i].l << ", " << Sa[i].r << "], " << Sa[i].v << ")";
        // }
        // Deb << ']' << std::endl;
        // Debug << "Si = [";
        // for (int i = 1; i <= Si.Cnt; ++i) {
        //     if (i > 1) Deb << ", ";
        //     Deb << "([" << Si[i].l << ", " << Si[i].r << "], " << Si[i].v << ")";
        // }
        // Deb << ']' << std::endl;
        // Debug << "Sg = [";
        // for (int i = 1; i <= Sg->Cnt; ++i) {
        //     if (i > 1) Deb << ", ";
        //     Deb << "([" << Sg->s[i].l << ", " << Sg->s[i].r << "], " << Sg->s[i].v << ")";
        // }
        // Deb << ']' << std::endl;
    }
    return 0;
}