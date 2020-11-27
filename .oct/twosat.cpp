#include <bits/stdc++.h>

#define pub push_back

namespace oct {

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

template <typename _Tp>
inline _Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}

template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}

}  // namespace oct

const int N = 1010005;
const int M = N << 2;

int cnt, snt, n, m, al, bl, av, bv;
int dfn[M], low[M], ist[M], col[M];

std::vector<int> to[M];
std::stack<int> st;

inline void tarjan(int u) {
    dfn[u] = low[u] = ++cnt, st.push(u), ist[u] = 1;
    for (int v : to[u]) {
        if (!dfn[v]) tarjan(v), oct::mid(low[u], low[v]);
        if (ist[v]) oct::mid(low[u], dfn[v]);
    }
    if (dfn[u] != low[u]) return;
    ++snt;
    while ((al = st.top()) != u) st.pop(), col[al] = snt, ist[al] = 0;
    st.pop(), col[al] = snt, ist[al] = 0;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> al >> av >> bl >> bv, al <<= 1, bl <<= 1;
        to[al - av].pub(bl - !bv), to[bl - bv].pub(al - !av);
    }
    for (int i = 1; i <= n << 1; ++i) dfn[i] ? void(0) : tarjan(i);
    for (int i = 1; i <= n; ++i) {
        if (col[i * 2] == col[i * 2 - 1]) return std::cout << "IMPOSSIBLE\n", 0;
    }
    std::cout << "POSSIBLE\n";
    for (int i = 1; i <= n; ++i) {
        std::cout << (col[i * 2] < col[i * 2 - 1]) << ' ';
    }
    std::cout << std::endl;
    return 0;
}