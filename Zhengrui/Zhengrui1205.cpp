#include <bits/stdc++.h>
const int N = 1000;
const int Np = N + 5;
int n, r, k;
int a[Np];
std::set<int> ans;
void dfs(int c);
inline void dfs(int c) {
    if (c == n + 1) {
        ans.insert(k);
        return;
    }
    if (a[c] == 0) {
        dfs(c + 1);
        return;
    }
    if (a[c] >= 2 && !r) {
        ----a[c];
        r = 1;
        dfs(c);
        r = 0;
        ++++a[c];
    }
    int tmp = std::min(a[c], std::min(a[c + 1], a[c + 2]));
    for (int i = a[c] % 3; i <= tmp; i += 3) {
        a[c + 1] -= i;
        a[c + 2] -= i;
        k += (a[c] - i) / 3;
        dfs(c + 1);
        k -= (a[c] - i) / 3;
        a[c + 1] += i;
        a[c + 2] += i;
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    dfs(1);
    std::cout << ans.size() << std::endl;
    return 0;
}