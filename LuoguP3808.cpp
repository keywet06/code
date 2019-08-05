#include <bits/stdc++.h>
const int C = 26;
const int N = 2000005;
char p[N];
int ans, cnt, n, now;
int is[N], next[N], vis[N];
int trie[N][C];
std::queue<int> queue;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", p);
        now = 0;
        for (int j = 0; p[j]; ++j) {
            p[j] -= 'a';
            if (!trie[now][p[j]]) {
                trie[now][p[j]] = ++cnt;
            }
            now = trie[now][p[j]];
        }
        ++is[now];
    }
    queue.push(0);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int i = 0; i < C; ++i) {
            if (trie[v][i]) {
                queue.push(trie[v][i]);
                next[trie[v][i]] = trie[next[v]][i];
            } else {
                trie[v][i] = trie[next[v]][i];
            }
        }
    }
    scanf("%s", p);
    now = 0;
    for (int i = 0; p[i]; ++i) {
        p[i] -= 'a';
        now = trie[now][p[i]];
        if (!vis[now]) {
            vis[now] = 1;
            ans += is[now];
        }
    }
    printf("%d\n", ans);
    return 0;
}