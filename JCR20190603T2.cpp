#include <bits/stdc++.h>
class node {
    public:
        int a, b, c;
};
int operator < (node, node);
const int N = 100;
int ans, cntx, cnty, n;
int ax[N], ay[N], xa[N], xb[N], ya[N], yb[N];
int map[N][N];
node sx[N], sy[N];
node makenode(int, int, int);
int main() {
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d %d", &xa[i], &yb[i], &xb[i], &ya[i]);
        sx[i * 2 - 1] = makenode(xa[i], i, 1);
        sx[i * 2] = makenode(xb[i], i, 2);
        sy[i * 2 - 1] = makenode(ya[i], i, 1);
        sy[i * 2] = makenode(yb[i], i, 2);
    }
    std::sort(sx + 1, sx + n * 2 + 1);
    std::sort(sy + 1, sy + n * 2 + 1);
    if (sx[1].c == 1) {
        xa[sx[1].b] = 1;
    } else {
        xb[sx[1].b] = 1;
    }
    ax[1] = 0;
    cntx = 1;
    for (int i = 2; i <= 2 * n; ++i) {
        if (sx[i - 1].a < sx[i].a) {
            ++cntx;
            ax[cntx] = sx[i].a - sx[i - 1].a;
            ++cntx;
            ax[cntx] = 0;
        }
        if (sx[i].c == 1) {
            xa[sx[i].b] = cntx;
        } else {
            xb[sx[i].b] = cntx;
        }
    }
    if (sy[1].c == 1) {
        ya[sy[1].b] = 1;
    } else {
        yb[sy[1].b] = 1;
    }
    ay[1] = 0;
    cnty = 1;
    for (int i = 2; i <= 2 * n; ++i) {
        if (sy[i - 1].a < sy[i].a) {
            ++cnty;
            ay[cnty] = sy[i].a - sy[i - 1].a;
            ++cnty;
            ay[cnty] = 0;
        }
        if (sy[i].c == 1) {
            ya[sy[i].b] = cnty;
        } else {
            yb[sy[i].b] = cnty;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = xa[i]; j <= xb[i]; ++j) {
            for (int k = ya[i]; k <= yb[i]; ++k) {
                map[j][k] = 1;
            }
        }
    }
    for (int i = 1; i <= cntx; ++i) {
        for (int j = 1; j <= cnty; ++j) {
            ans += map[i][j] * ax[i] * ay[j];
        }
    }
    printf("%d\n", ans);
    return 0;
}
inline node makenode(int a, int b, int c) {
    node tmp;
    tmp.a = a;
    tmp.b = b;
    tmp.c = c;
    return tmp;
}
inline int operator < (node a, node b) {
    return a.a < b.a;
}