#include <bits/stdc++.h>

const int N = 20005;
const int K = 55;

int n, k, On, Ans;
int Num[N], b[N], a[N], e[N], A[N];

inline int Mex() {
    int i = 0;
    while (Num[i]) ++i;
    return i;
}

inline void dfs(int c) {
    if (c == n + 1) {
        ++Ans;
        ++A[e[1] + e[2] + e[3] + e[4]];
        for (int i = 1; i <= n; ++i) std::cout << e[i] << " :"[i == n];
        for (int i = 1; i <= n; ++i) std::cout << a[i] << " \n"[i == n];
        return;
    }
    for (int i = 0; i <= n; ++i) {
        ++Num[i], a[c] = i;
        if (std::abs((e[c] = Mex()) - b[c]) <= k) dfs(c + 1);
        --Num[i];
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> b[i];
    dfs(1);
    std::cout << Ans << std::endl;
    for (int i = 0; i <= n; ++i) std::cout << A[i] << " \n"[i == n];
    return 0;
}