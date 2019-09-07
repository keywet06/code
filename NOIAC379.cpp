#include <bits/stdc++.h>
const int C = 26;
const int N = 200000;
int cn, cnt, n, now, tmp;
int vis[N], is[N], fail[N], next[N], to[N], head[N];
int trie[N][C];
std::queue<int> queue;
std::string s[N + 5];
void insert(int, int);
void addedge(int, int);
void dfs(int);
int main() {
    scanf("%d", &n);
    for (int i = 0; i < C; ++i) {
        trie[0][i] = 1;
    }
    cnt = 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s[i];
        now = 1;
        for (int j = 0; j < s[i].length(); ++j) {
            s[i][j] -= 'a';
            if (!trie[now][s[i][j]]) {
                trie[now][s[i][j]] = ++cnt;
                // insert(now, cnt);
            }
            now = trie[now][s[i][j]];
            ++is[now];
        }
    }
    queue.push(1);
    while (!queue.empty()) {
        now = queue.front();
        queue.pop();
        for (int i = 0; i < C; ++i) {
            if (trie[now][i]) {
                queue.push(trie[now][i]);
                tmp = fail[now];
                while (!trie[tmp][i]) {
                    tmp = fail[tmp];
                }
                fail[trie[now][i]] = trie[tmp][i];
            }
        }
    }
    for (int i = 2; i <= cnt; ++i) {
        insert(fail[i], i);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        now = 1;
        for (int j = 0; j < s[i].length(); ++j) {
            now = trie[now][s[i][j]];
        }
        printf("%d\n", is[now]);
    }
    return 0;
}
inline void insert(int x, int y) {
    ++cn;
    next[cn] = head[x];
    head[x] = cn;
    to[cn] = y;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline void dfs(int v) {
    vis[v] = 1;
    for (int u = head[v]; u; u = next[u]) {
        if (!vis[to[u]]) {
            dfs(to[u]);
        }
        is[v] += is[to[u]];
    }
}