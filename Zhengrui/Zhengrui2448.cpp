#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

struct Convert {
    int c00, c01, c10, c11;
    Convert(int a = 0, int b = 0, int c = 0, int d = 0) : c00(a), c01(b), c10(c), c11(d) {}
};

const int INF = 1000000;

const Convert B[2] = {Convert(0, 1, INF, INF), Convert(INF, INF, 1, 0)};

inline Convert operator+(Convert a, Convert b) {
    return Convert(std::min(a.c00 + b.c00, a.c01 + b.c10), std::min(a.c00 + b.c01, a.c01 + b.c11),
                   std::min(a.c10 + b.c00, a.c11 + b.c10), std::min(a.c10 + b.c01, a.c11 + b.c11));
}

const int C = 20;
const int N = 400005;

int n, q;
int Nod[N], Dep[N], Id[N];

std::string s;

std::vector<int> Son[N];

int St, Sta[N];

int Fa[N][C];
Convert An[N][C];

inline void Dfs(int u) {
    for (int i = 1; i < C; ++i) {
        Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
        An[u][i] = An[u][i - 1] + An[Fa[u][i - 1]][i - 1];
    }
    auto &S = Son[u];
    int n = S.size();
    for (int i = 0; i < n; ++i) {
        int a = i << 1 | 1, b = n - i - 1 << 1 | 1;
        Fa[S[i]][0] = u, Dep[S[i]] = Dep[u] + 1, Id[S[i]] = i;
        An[S[i]][0] = Convert(std::min(a, b + 2), std::min(a + 1, b + 1), std::min(a + 1, b + 1), std::min(a + 2, b));
        Dfs(S[i]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> s >> q, n = s.length(), s = ' ' + s;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '(') {
            Son[Sta[St]].push_back(i), Nod[i] = Sta[++St] = i;
        } else {
            Nod[i] = Sta[St--];
        }
    }
    Dfs(0);
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        int uc = s[u] == ')', vc = s[v] == ')';
        u = Nod[u], v = Nod[v];
        if (Dep[v] > Dep[u]) std::swap(u, v), std::swap(uc, vc);
        Convert U = B[uc], V = B[vc];
        int x = Dep[u] - Dep[v];
        for (int i = 0; i < C; ++i) {
            if ((x >> i) & 1) U = U + An[u][i], u = Fa[u][i];
        }
        if (u == v) {
            std::cout << (vc ? (uc ? U.c11 : U.c01) : (uc ? U.c10 : U.c00)) << '\n';
            continue;
        }
        for (int i = C - 1; i >= 0; --i) {
            if (Fa[u][i] != Fa[v][i]) {
                U = U + An[u][i], u = Fa[u][i];
                V = V + An[v][i], v = Fa[v][i];
            }
        }
        int n = Son[Fa[u][0]].size(), ui = Id[u], vi = Id[v];
        if (ui > vi) std::swap(u, v), std::swap(uc, vc), std::swap(U, V), std::swap(ui, vi);
        int u0, u1, v0, v1;
        uc ? (u0 = U.c10, u1 = U.c11) : (u0 = U.c00, u1 = U.c01);
        vc ? (v0 = V.c10, v1 = V.c11) : (v0 = V.c00, v1 = V.c01);
        int Ans = u1 + v0 + (vi - ui - 1 << 1 | 1);
        if (Fa[u][0]) Ans = std::min(Ans, u0 + v1 + (ui + n - vi << 1 | 1));
        std::cout << Ans << '\n';
    }
    return 0;
}