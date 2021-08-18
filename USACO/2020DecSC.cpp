#include <bits/stdc++.h>

const int N = 1005;

int n, cx, cy, tx, ty, p;
int ans[N], lx[N], ly[N], xi[N], yi[N], ud[N], deg[N], bt[N], sum[N], vs[N];

std::string s;

std::vector<int> to[N];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s >> lx[i] >> ly[i];
        (s[0] == 'N' ? xi[cx++] : yi[cy++]) = i;
    }
    std::sort(xi, xi + cx, [](int x, int y) { return lx[x] < lx[y]; });
    std::sort(yi, yi + cy, [](int x, int y) { return ly[x] < ly[y]; });
    for (int i = 0; i < cx; ++i) {
        for (int j = 0; j < cy; ++j) {
            if (ud[yi[j]]) continue;
            if (lx[xi[i]] < lx[yi[j]] || ly[yi[j]] < ly[xi[i]]) continue;
            tx = ly[yi[j]] - ly[xi[i]], ty = lx[xi[i]] - lx[yi[j]];
            if (tx == ty) continue;
            if (tx < ty) ud[yi[j]] = 1, ans[yi[j]] = ty, bt[yi[j]] = xi[i];
            if (tx > ty) {
                ud[xi[i]] = 1, ans[xi[i]] = tx, bt[xi[i]] = yi[j];
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (ud[i]) ++deg[bt[i]];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!vs[j] && !deg[j]) {
                p = j;
                break;
            }
        }
        vs[p] = 1, --deg[bt[p]], sum[bt[p]] += sum[p] + 1;
    }
    for (int i = 1; i <= n; ++i) std::cout << sum[i] << std::endl;
    for (int i = 1; i <= n; ++i) {
        
    }
    return 0;
}