#include <bits/stdc++.h>
const int B = 2;
const int N = 1100005;
int n, m, root, cnt;
int size[N], val[N], num[N], fa[N], a[N];
int son[N][B];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    a[0] = -1;
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        if (a[i] != a[i - 1]) {
            val[++cnt] = a[i];
            num[cnt] = 1;
            fa[cnt] = cnt - 1;
            size[cnt] = n - i + 1;
            son[cnt][1] = cnt + 1;
        } else {
            ++num[i];
        }
    }
    son[cnt][1] = 0;
    for (int i = 1; i <= n; ++i) {
        
    }
    return 0;
}