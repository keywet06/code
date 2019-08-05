#include <bits/stdc++.h>
const int C = 26;
const int N = 2000005;
char p[N];
int ans, cnt, lp, n, now;
int is[N], next[N];
int trie[N][C];
std::queue<int> queue;
int main() {
    scanf("%d", &n);
    ++cnt;
    for (int i = 0; i < C; ++i) {
        trie[0][i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%s", p);
        lp = strlen(p);
        now = 1;
        for (int j = 0; j < lp; ++j) {
            p[j] -= 'a';
            if (!trie[now][p[j]]) {
                trie[now][p[j]] = ++cnt;
            }
            now = trie[now][p[j]];
        }
        ++is[now];
    }
    queue.push(1);
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
    lp = strlen(p);
    now = 1;
    for (int i = 0; i < lp; ++i) {
        p[i] -= 'a';
        now = trie[now][p[i]];
        ans += is[now];
        is[now] = 0;
    }
    printf("%d\n", ans);
    return 0;
}