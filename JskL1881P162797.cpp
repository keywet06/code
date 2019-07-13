#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
const int B = sqrt(N);
int a[N], cnt[N], n, m, tans, ans[N];
struct Q {
    int l, r, id;
	bool operator < (const Q &t) const {
        return l / B == t.l / B ? r < t.r : l / B < t.l / B;
    }
}q[N];
void update(int x, int f) {
    cnt[x] += f;
    if (cnt[x] == 0 && f == -1) tans--;
    if (cnt[x] == 1 && f == 1) tans++;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (l < q[i].l) update(a[l++], -1);
        while (l > q[i].l) update(a[--l], 1);
        while (r < q[i].r) update(a[++r], 1);
        while (r > q[i].r) update(a[r--], -1);
        ans[q[i].id] = tans;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}