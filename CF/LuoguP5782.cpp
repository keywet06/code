#include <bits/stdc++.h>

const int N = 1000005;
const int N1 = N << 1;
const int N2 = N << 2;

struct edge {
    int t, next;
};

bool in[N1];

int cur, n, tim, top, cnt, m;
int head[N1], low[N1], dfn[N1], stack[N1], scc[N1];

edge ed[N2];

void add(int u, int v) {
    ed[++cur].t = v, ed[cur].next = head[u], head[u] = cur;
}

void tarjan(int u) {
    low[u] = dfn[u] = ++tim, stack[top++] = u, in[u] = true;
    for (int i = head[u]; i; i = ed[i].next) {
        int v = ed[i].t;
        if (!dfn[v]) {
            tarjan(v), low[u] = std::min(low[u], low[v]);
        } else if (in[v])
            low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;
        cnt++;
        do {
            v = stack[--top];
            in[v] = false;
            scc[v] = cnt;
        } while (u != v);
    }
}

bool two_SAT() {
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n]) return false;
    }
    return true;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, aval, bval;
        std::cin >> a >> b;
        aval = ++a % 2, a /= 2;
        bval = ++b % 2, b /= 2;
        int nota = aval ^ 1, notb = bval ^ 1;
        add(a + nota * n, b + bval * n);
        add(b + notb * n, a + aval * n);
    }
    if (two_SAT()) {
        for (int i = 1; i <= n; i++) std::cout << 2 * i - (scc[i] > scc[i + n]) << '\n';
    } else {
        std::cout << "NIE\n";
    }
    return 0;
}