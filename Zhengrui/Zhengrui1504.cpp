#include <bits/stdc++.h>
const int C = 26;
const int K = 1000005;
const int N1 = 1005;
int n, cnt;
int next[K], e[K];
int trie[K][C];
std::string s;
void insert(std::string s) {
    int u = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!trie[u][s[i]]) trie[u][s[i]] = ++cnt;
        u = trie[u][s[i]];
        ++e[u];
    }
}
void build() {
    std::queue<int> q;
    for (int i = 0; i < C; i++) {
        if (trie[0][i]) q.push(trie[1][i]);
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < C; i++) {
            if (trie[u][i]) {
                next[trie[u][i]] = trie[next[u]][i];
                q.push(trie[u][i]);
            } else {
                trie[u][i] = trie[next[u]][i];
            }
        }
    }
}
namespace Subtask1 {
const int N = 1005;
int dp[N][N];
int main() {
    for (int i = 1; i <= n; ++i) insert(s.substr(i));
    build();
    for (int l = 1; l <= n; ++l) {
        int now = trie[0][s[l]];
        dp[l][l] = e[now];
        for (int r = l + 1; r <= n; ++r) {
            now = trie[now][s[r]];
            dp[l][r] = std::max(dp[l + 1][r], dp[l][r - 1]) + e[now];
        }
    }
    std::cout << dp[1][n] << std::endl;
    return 0;
}
}  // namespace Subtask1
namespace Subtask2 {
    const int N = 50005;
    const int O = 21;
int dp[N][O];
int main() {
    for (int i = 1; i <= n; ++i) insert(s.substr(i, O - 1));
    build();
    int ans = 0;
    for (int l = 1; l <= n; ++l) {
        int now = trie[0][s[l]];
        dp[l][1] = e[now];
        for (int r = l + 1; r <= std::min(l + O - 2, n); ++r) {
            now = trie[now][s[r]];
            dp[l][r - l] = std::max(dp[l + 1][r - l - 1], dp[l][r - l - 1]) + e[now];
            ans = std::max(ans, dp[l][r - 1]);
        }
    }
    std::cout << ans + (n - O + 1) << std::endl;
    return 0;
}
}  // namespace Subtask2
namespace Subtask3 {
int main() {
    std::cout << "dlsddl" << std::endl;
    return 0;
}
}  // namespace Subtask3
int main() {
    std::cin >> s;
    n = s.size();
    s = 'a' + s;
    for (int i = 0; i < s.size(); ++i) s[i] -= 'a';
    return s.size() <= 1000
               ? Subtask1::main()
               : (s.size() <= 50000 ? Subtask2::main() : Subtask3::main());
}