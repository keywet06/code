#include <cstdio>
#include <cstring>
using namespace std;
class dxlb {
   public:
    int now, next;
};
class tu {
   public:
    dxlb edge[10000005];
    int head[1005], in[1005];
    int cnt, n;
};
void edge_insert(tu& t, int x, int y) {
    ++t.in[y];
    ++t.cnt;
    t.edge[t.cnt].next = t.head[x];
    t.head[x] = t.cnt;
    t.edge[t.cnt].now = y;
    return;
}
int tuopu(tu t) {
    int x = 0, y = t.n, len = 0;
    int a[1005], b[1005];
    memset(b, 0, sizeof(b));
    while (y) {
        ++x;
        len = 0;
        for (int i = 1; i <= t.n; ++i) {
            if (!b[i] && !t.in[i]) {
                ++len;
                a[len] = i;
                b[i] = 1;
                --y;
            }
        }
        for (int i = 1; i <= len; ++i) {
            int u = t.head[a[i]];
            while (u) {
                --t.in[t.edge[u].now];
                u = t.edge[u].next;
            }
        }
    }
    return x;
}
tu t;
int m, len1, len2;
int a[1005], b[1005];
int main() {
    scanf("%d %d", &t.n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &len1, &a[1]);
        len2 = 0;
        for (int j = 2; j <= len1; ++j) {
            scanf("%d", &a[j]);
            for (int k = a[j - 1] + 1; k < a[j]; ++k) {
                ++len2;
                b[len2] = k;
            }
        }
        for (int j = 1; j <= len1; ++j) {
            for (int k = 1; k <= len2; ++k) {
                edge_insert(t, a[j], b[k]);
            }
        }
    }
    printf("%d\n", tuopu(t));
    return 0;
}
