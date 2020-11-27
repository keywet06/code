#include <bits/stdc++.h>

inline int read() {
    int res = 0;
    bool bo = 0;
    char c;
    while (((c = getchar()) < '0' || c > '9') && c != '-')
        ;
    if (c == '-')
        bo = 1;
    else
        res = c - 48;
    while ((c = getchar()) >= '0' && c <= '9')
        res = (res << 3) + (res << 1) + (c - 48);
    return bo ? ~res + 1 : res;
}

inline char get() {
    char c;
    while ((c = getchar()) != 'A' && c != 'B' && c != 'C')
        ;
    return c;
}

const int N = 2e5 + 5;
int n, d, m, a1[N], b1[N], ecnt, nxt[N], adj[N], go[N], dfn[N], low[N], times,
    num, bel[N], top, stk[N], cyx[N];
char s[N], a2[N], b2[N], orz[N];
bool ins[N], flag;

void addedge(int u, int v) {
    nxt[++ecnt] = adj[u];
    adj[u] = ecnt;
    go[ecnt] = v;
}

int neg(int x) { return x > n ? x - n : x + n; }

int tran(int x, char c) {
    if (s[x] == 'a') return c == 'B' ? x : x + n;
    if (s[x] == 'b' || s[x] == 'c') return c == 'A' ? x : x + n;
    if (c == 'C') return x + n;
    return x;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++times;
    ins[stk[++top] = u] = 1;
    for (int e = adj[u], v; e; e = nxt[e]) {
        if (!dfn[v = go[e]]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        bel[u] = ++num;
        ins[u] = 0;
        while (v = stk[top--], v != u) bel[v] = num, ins[v] = 0;
    }
}

bool solve() {
    int i;
    ecnt = times = num = 0;
    for (i = 1; i <= (n << 1); i++) bel[i] = adj[i] = dfn[i] = 0;
    for (i = 1; i <= m; i++)
        if (s[a1[i]] != 'x' && s[b1[i]] != 'x') {
            if (a2[i] == s[a1[i]] - 32) continue;
            int u = tran(a1[i], a2[i]), v;
            if (b2[i] == s[b1[i]] - 32) {
                addedge(u, neg(u));
                continue;
            }
            v = tran(b1[i], b2[i]);
            addedge(u, v);
            addedge(neg(v), neg(u));
        } else {
            char o = s[a1[i]], p = s[b1[i]];
            int u, v, x = cyx[a1[i]], y = cyx[b1[i]];
            if (o == 'x' && p == 'x') {
                if (a2[i] == orz[x]) continue;
                u = tran(a1[i], a2[i]), v;
                if (b2[i] == orz[y]) {
                    addedge(u, neg(u));
                    continue;
                }
                v = tran(b1[i], b2[i]);
                addedge(u, v);
                addedge(neg(v), neg(u));
            } else if (o == 'x' && p != 'x') {
                if (a2[i] == orz[x]) continue;
                u = tran(a1[i], a2[i]), v;
                if (b2[i] == s[b1[i]] - 32) {
                    addedge(u, neg(u));
                    continue;
                }
                v = tran(b1[i], b2[i]);
                addedge(u, v);
                addedge(neg(v), neg(u));
            } else {
                if (a2[i] == s[a1[i]] - 32) continue;
                u = tran(a1[i], a2[i]), v;
                if (b2[i] == orz[y]) {
                    addedge(u, neg(u));
                    continue;
                }
                v = tran(b1[i], b2[i]);
                addedge(u, v);
                addedge(neg(v), neg(u));
            }
        }
    for (i = 1; i <= (n << 1); i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (i = 1; i <= n; i++) {
        if (bel[i] == bel[i + n]) return 0;
    }
    for (i = 1; i <= n; i++) {
        if (bel[i] < bel[i + n]) {
            if (s[i] == 'a') {
                std::cout << 'B';
            } else if (s[i] == 'b' || s[i] == 'C') {
                std::cout << 'A';
            } else if (orz[cyx[i]] == 'A') {
                std::cout << 'B';
            } else {
                std::cout << 'A';
            }
        } else {
            if (s[i] == 'a' || s[i] == 'b') {
                std::cout << 'C';
            } else if (s[i] == 'c') {
                std::cout << 'B';
            } else if (orz[cyx[i]] == 'A') {
                std::cout << 'C';
            } else {
                std::cout << 'B';
            }
        }
    }
    return 1;
}
void dfs(int dep) {
    if (dep > d) {
        if (!flag) flag = solve();
        if (flag) exit(0);
        return;
    }
    orz[dep] = 'A';
    dfs(dep + 1);
    orz[dep] = 'B';
    dfs(dep + 1);
}
int main() {
    int i;
    n = read();
    read();
    scanf("%s", s + 1);
    m = read();
    for (i = 1; i <= n; i++) {
        if (s[i] == 'x') cyx[i] = ++d;
    }
    for (i = 1; i <= m; i++) {
        a1[i] = read(), a2[i] = get(), b1[i] = read(), b2[i] = get();
    }
    dfs(1);
    if (!flag) puts("-1");
    return 0;
}