#ifndef STD_BITS_STDCPP_H
#define STD_BITS_STDCPP_H
#include <bits/stdc++.h>
#endif
#include "kw/Tu.hpp"
const int M = 2000005;
const int N = 1000005;
int n, x, y, z;
int size[N];
long long ans;
kw::Tu<N, M, int> Tu;
void dfs(int, int);
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        Tu.addedge(x, y, z);
    }
    dfs(1, 1);
    printf("%lld\n", ans);
    return 0;
}
inline void dfs(int v, int fa) {
    size[v] = 1;
    for (kw::Tu<N, M, int>::iterator it = Tu.GetHead(v); it; it = it->next) {
        if (it->to == fa) {
            continue;
        }
        dfs(it->to, v);
        ans += std::abs(n - size[it->to] * 2LL) * it->data;
        size[v] += size[it->to];
    }
}