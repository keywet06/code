#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

template <typename Type>
using PriorityQueue = std::priority_queue<Type, std::vector<Type>, std::greater<Type> >;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<int> > To(n + 1);
    for (int i = 2; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 1; j < i; ++j) {
            if (s[j - 1] == '0') continue;
            To[i].push_back(j);
            To[j].push_back(i);
        }
    }
    std::vector<int> Len(n + 1, n << 3);
    for (int R = 1; R <= n; ++R) {
        std::vector<int> Dis(n + 1), In(n + 1), Vis(n + 1), Fa(n + 1), Cyc(n + 1, n << 3);
        std::queue<int> Que;
        std::stack<int> Nodes;
        Que.push(R), In[R] = 1, Fa[R] = R;
        while (!Que.empty()) {
            int u = Que.front();
            Vis[u] = 1, Que.pop(), Nodes.push(u);
            for (int v : To[u]) {
                if (v == Fa[u]) continue;
                if (!In[v]) {
                    In[v] = 1, Que.push(v), Dis[v] = Dis[u] + 1, Fa[v] = u;
                } else if (Vis[v]) {
                    Mid(Cyc[u], Dis[u] + Dis[v] + 1);
                    Mid(Cyc[v], Dis[u] + Dis[v] + 1);
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) std::cout << Len[i] << '\n';
    return 0;
}