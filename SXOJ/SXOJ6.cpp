#include <bits/stdc++.h>

const int C = 10;
const int N = 1e6 + 5;

int P, t, u, v;
int ban[C];
int di[N], fr[N];

std::queue<int> q;

std::stack<char> s;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> P >> t;
    while (t--) std::cin >> u, ban[u] = 1;
    for (int i = 1; i < C; ++i) {
        if (!ban[i] && !di[i % P]) di[i % P] = i + 1, q.push(i % P);
    }
    while (!q.empty()) {
        u = q.front(), q.pop();
        for (int i = 0; i < C; ++i) {
            if (ban[i]) continue;
            v = (u * 10 + i) % P;
            if (di[v]) continue;
            di[v] = i + 1, fr[v] = u, q.push(v);
        }
    }
    if (!di[0]) return std::cout << -1 << '\n', 0;
    s.push(di[0] + '0' - 1);
    for (u = fr[0]; u; u = fr[u]) s.push(di[u] + '0' - 1);
    while (!s.empty()) std::cout << s.top(), s.pop();
    std::cout << '\n';
    return 0;
}
