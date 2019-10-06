#include <bits/stdc++.h>
const int C = 10;
const int D = 2;
const int N = 2005;
const long long mod = 1000000007;
int cnt = 1, m, n, now, k, v;
int next[N], is[N];
int trie[N][C];
long long ans;
long long dp[N][N][D];
std::queue<int> queue;
std::string s, s1;
int main() {
    for (int i = 0; i < C; ++i) {
        trie[0][i] = 1;
    }
    std::ios::sync_with_stdio(0);
    std::cin >> s;
    n = s.length();
    for (int i = 0; i < n; ++i) {
        s[i] -= '0';
    }
    std::cin >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> s1;
        k += s1.length();
        now = 1;
        for (int j = 0; j < s1.length(); ++j) {
            s1[j] -= '0';
            if (!trie[now][s1[j]]) {
                trie[now][s1[j]] = ++cnt;
                is[cnt] |= is[now];
            }
            now = trie[now][s1[j]];
        }
        is[now] = 1;
    }
    queue.push(1);
    while (!queue.empty()) {
        now = queue.front();
        queue.pop();
        for (int i = 0; i < C; ++i) {
            if (trie[now][i]) {
                next[trie[now][i]] = trie[next[now]][i];
                is[trie[now][i]] |= is[next[trie[now][i]]];
                queue.push(trie[now][i]);
            } else {
                trie[now][i] = trie[next[now]][i];
            }
        }
    }
    for (int i = 1; i < s[0]; ++i) {
        ++dp[0][trie[1][i]][0];
    }
    ++dp[0][trie[1][s[0]]][1];
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < C; ++j) {
            ++dp[i][trie[1][j]][0];
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j <= cnt; ++j) {
            if (is[j] || !(dp[i][j][0] | dp[i][j][1])) {
                continue;
            }
            for (int l = 0; l < C; ++l) {
                (dp[i + 1][trie[j][l]][0] += dp[i][j][0]) %= mod;
            }
            if (!dp[i][j][1]) {
                continue;
            }
            for (int l = 0; l < s[i + 1]; ++l) {
                (dp[i + 1][trie[j][l]][0] += dp[i][j][1]) %= mod;
            }
            (dp[i + 1][trie[j][s[i + 1]]][1] += dp[i][j][1]) %= mod;
        }
    }
    for (int j = 0; j <= cnt; ++j) {
        if (!is[j]) {
            (ans += dp[n - 1][j][0] + dp[n - 1][j][1]) %= mod;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
