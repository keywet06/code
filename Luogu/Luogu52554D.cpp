#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::string T, S;
    std::cin >> T >> S, T += ' ';
    std::vector<int> Fail(n + 1);
    Fail[0] = -1;
    for (int i = 1; i <= n; ++i) {
        int &x = Fail[i] = Fail[i - 1];
        while (x >= 0 && T[x + 1] != T[i]) x = Fail[x];
        x += T[x + 1] == T[i];
    }
    std::vector<int> Ans(m);
    for (int i = 0, u = -1; i < m; ++i) {
        while (u >= 0 && T[u + 1] != S[i]) u = Fail[u];
        u += T[u + 1] == S[i];
        if (u == -1) return std::cout << "Fake" << std::endl, 0;
        Ans[i] = u == i ? 1 : Ans[i - u - 1] + 1;
    }
    std::cout << Ans.back() << std::endl;
    return 0;
}