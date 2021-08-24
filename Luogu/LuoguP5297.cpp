#include <bits/stdc++.h>

using int64 = long long;
#define pub push_back

const int N = 505;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool ins[N];
bool _cov[N][N], cov0[N][N], cov1[N][N];

char str[N][N];

int R, C, T, idx, top, head, tail, tot, iscc;
int dfn[N], low[N], stk[N], que[N], deg[N], pos[N], scc[N];
int id[N][N];

std::vector<int> adj[N], ebk[N];
std::vector<int> cov[N][N];

bool inG(int x, int y) {
    return x >= 1 && x <= R && y >= 1 && y <= C && str[x][y] != '#';
}
bool beam(int x, int y) { return str[x][y] == '|' || str[x][y] == '-'; }
bool dfs(bool cov[N][N], int x, int y, int d) {
    cov[x][y] = true;
    if (!inG(x + dx[d], y + dy[d])) return true;
    int nx = x + dx[d], ny = y + dy[d];
    if (beam(nx, ny)) return false;
    if (str[nx][ny] == '.') {
        return dfs(cov, nx, ny, d);
    } else {
        return dfs(cov, nx, ny, d ^ (str[nx][ny] == '/' ? 1 : 3));
    }
}
void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++top] = u;
    ins[u] = true;
    for (unsigned j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        if (!dfn[v]) {
            tarjan(v), low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] != dfn[u]) return;
    scc[u] = ++iscc;
    while (stk[top] != u) {
        int v = stk[top--];
        ins[v] = false;
        scc[v] = iscc;
    }
    ins[u] = false;
    top--;
}
void solve() {
    scanf("%d %d", &R, &C);
    for (int i = 1; i <= R; i++) scanf("%s", str[i] + 1);
    for (int i = 1; i <= tot * 2 + 1; i++) adj[i].clear(), ebk[i].clear();
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) cov[i][j].clear();
    }
    memset(_cov, 0, sizeof(_cov));
    memset(dfn, 0, sizeof(dfn));
    tot = idx = iscc = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (beam(i, j)) {
                id[i][j] = ++tot;
                memset(cov0, 0, sizeof(cov0));
                bool tag0 = dfs(cov0, i, j, 1) & dfs(cov0, i, j, 3);
                memset(cov1, 0, sizeof(cov1));
                bool tag1 = dfs(cov1, i, j, 0) & dfs(cov1, i, j, 2);
                if (!tag0 && !tag1) return printf("IMPOSSIBLE\n"), void(0);
                if (!tag0) {
                    for (int x = 1; x <= R; x++) {
                        for (int y = 1; y <= C; y++) {
                            if (str[x][y] == '.' && cov1[x][y]) {
                                cov[x][y].pub(tot << 1 | 1);
                            }
                        }
                    }
                    adj[tot << 1].pub(tot << 1 | 1);
                } else if (!tag1) {
                    for (int x = 1; x <= R; x++) {
                        for (int y = 1; y <= C; y++) {
                            if (str[x][y] == '.' && cov0[x][y]) {
                                cov[x][y].pub(tot << 1);
                            }
                        }
                    }
                    adj[tot << 1 | 1].pub(tot << 1);
                } else {
                    for (int x = 1; x <= R; x++) {
                        for (int y = 1; y <= C; y++) {
                            if (str[x][y] == '.') {
                                if (cov0[x][y] && cov1[x][y])
                                    _cov[x][y] = true;
                                else if (cov0[x][y]) {
                                    cov[x][y].pub(tot << 1);
                                } else if (cov1[x][y]) {
                                    cov[x][y].pub(tot << 1 | 1);
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                if (str[i][j] == '.' && !_cov[i][j]) {
                    int siz = cov[i][j].size(), u, v;
                    if (siz == 0) {
                        return printf("IMPOSSIBLE\n"), void(0);
                    } else if (siz == 1)
                        u = cov[i][j][0], adj[u ^ 1].pub(u);
                    else if (siz == 2)
                        u = cov[i][j][0], v = cov[i][j][1], adj[u ^ 1].pub(v),
                        adj[v ^ 1].pub(u);
                }
    }
    for (int i = 2; i <= (tot << 1 | 1); i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= tot; i++) {
        if (scc[i << 1] == scc[i << 1 | 1]) {
            return printf("IMPOSSIBLE\n"), void(0);
        }
    }
    for (int v, u = 2; u <= (tot << 1 | 1); u++) {
        for (unsigned j = 0; j < adj[u].size(); j++) {
            if (scc[v = adj[u][j]] != scc[u]) {
                ebk[scc[v]].pub(scc[u]), deg[scc[u]]++;
            }
        }
    }
    head = 1;
    tail = 0;
    for (int i = 1; i <= iscc; i++) {
        if (!deg[i]) que[++tail] = i;
    }
    while (head <= tail) {
        int u = que[head];
        pos[u] = head++;
        for (unsigned j = 0; j < ebk[u].size(); j++) {
            int v = ebk[u][j];
            if (!--deg[v]) que[++tail] = v;
        }
    }
    for (int i = 1; i <= tot * 2 + 1; i++) ebk[i].clear(), adj[i].clear();
    printf("POSSIBLE\n");
}
int main() {
    for (std::cin >> T; T; T--) solve();
    return 0;
}