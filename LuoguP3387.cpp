#include <bits/stdc++.h>
const int m_MAX = 100005;
const int n_MAX = 10005;
std::stack<int> st;
int ans, cnt, cnt2, cnt3, m;
int n, x, y;
int dfn[n_MAX], dp[n_MAX], ds[n_MAX], head[n_MAX], head2[n_MAX];
int in[n_MAX], low[n_MAX], out[n_MAX], sta[n_MAX], val[n_MAX];
int vals[n_MAX];
int next[m_MAX], next2[m_MAX], to[m_MAX], to2[m_MAX];
void insert(int, int);
void tarjan(int);
void insert2(int, int);
int dfs(int);
int main() {
    scanf("%d, %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", val[i]);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        insert(x, y);
    }
    cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i) {
        vals[dfn[i]] += val[i];
        for (int u = head[i]; u; u = next[u])
            if (dfn[to[u]] != dfn[i]) insert2(ds[dfn[i]], ds[dfn[to[u]]]);
    }
    for (int i = 1; i <= cnt2; ++i)
        if (!in[i]) dp[i] = vals[i];
    for (int i = 1; i <= cnt2; ++i)
        if (!out[i]) ans = std::max(ans, dfs(i));
    printf("%d\n", ans);
    return 0;
}
inline void insert(int a, int b) {
    ++cnt;
    next[cnt] = head[a];
    head[a] = cnt;
    to[a] = b;
}
inline void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    sta[u] = 1;
    for (int v = head[u]; v; v = next[v])
        if (!dfn[to[v]]) {
            tarjan(to[v]);
            low[u] = std::min(low[u], low[v]);
        } else if (sta[to[v]])
            low[u] = std::min(low[u], low[v]);
    if (dfn[u] == low[u]) {
        ++cnt2;
        ds[dfn[u]] = cnt2;
        while (st.top() != u) st.pop();
    }
}
inline void insert2(int a, int b) {
    ++cnt3;
    next2[cnt3] = head2[a];
    head2[a] = cnt3;
    to2[a] = b;
    ++out[a];
    ++in[b];
}
inline int dfs(int u) {
    if (!dp[u])
        for (int v = head2[u]; v; v = next[v])
            dp[u] = std::max(dp[u], dfs(to[v]));
    return dp[u];
}
