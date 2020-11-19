#include <bits/stdc++.h>
#define maxn 1000005
using namespace std;
int a[maxn];
int T, n, k, x, y;

int b[maxn << 1], c[maxn << 1];
int idb[maxn << 1], idc[maxn << 1];
int ans[maxn], pre[maxn];
int link[maxn];
int head1, head2, tail1, tail2;

void work() {
    for (int i = 1; i <= n; i++) pre[i] = link[i] = 0;
    for (int i = 1; i <= n; i++)
        b[n - i + 1 + maxn] = a[i], idb[n - i + 1 + maxn] = i;

    head1 = 1 + maxn, tail1 = n + maxn;
    head2 = 1 + maxn, tail2 = 0 + maxn;

    int shang = -1;
    for (int turn = 1; turn < n; turn++) {
        int zd, zx;
        int zuida, zuixiao;
        int zd1, zd2, zx1, zx2;
        int zh1, zh2, xh1, xh2;
        if (head1 <= tail1)
            zd1 = b[head1], zx1 = b[tail1], zh1 = idb[head1], xh1 = idb[tail1];
        else
            zd1 = -1, zx1 = 999999999;
        if (head2 <= tail2)
            zd2 = c[head2], zx2 = c[tail2], zh2 = idc[head2], xh2 = idc[tail2];
        else
            zd2 = -1, zx2 = 999999999;
        if (zd2 > zd1 || (zd2 == zd1 && zh2 > zh1)) {
            zd = idc[head2];
            zuida = zd2;
            head2++;
        } else {
            zd = idb[head1];
            zuida = zd1;
            head1++;
        }
        if (zx2 < zx1 || (zx2 == zx1 && xh2 < xh1)) {
            zx = idc[tail2];
            zuixiao = zx2;
            tail2--;
        } else {
            zx = idb[tail1];
            zuixiao = zx1;
            tail1--;
        }

        if (pre[zx] != 0) {
            if (shang == -1 || shang == pre[zx]) {
                link[turn] = pre[zx];
            } else
                break;
            shang = turn;
        }
        pre[zd] = turn;
        int tt = zuida - zuixiao;
        int id = zd;
        tail2++;
        c[tail2] = tt;
        idc[tail2] = zd;
        int now = tail2;
        while (now > head2) {
            if (c[now] < c[now - 1] ||
                (c[now] == c[now - 1] && idc[now] < idc[now - 1]))
                break;
            swap(c[now], c[now - 1]);
            swap(idc[now], idc[now - 1]);
            now--;
        }
    }
    int zuixiao = n;
    for (int i = n; i >= 1; i--)
        if (link[i]) {
            int now = i, flag = 0;
            while (now != 0) {
                if (flag == 1) zuixiao = min(zuixiao, now);
                int pp = now;
                now = link[now];
                link[pp] = 0;
                flag = 1 - flag;
            }
        }
    cout << n - zuixiao + 1 << endl;
    return;
}

int main() {
    scanf("%d", &T), scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    work(), T--;
    while (T--) {
        scanf("%d", &k);
        while (k--) {
            scanf("%d%d", &x, &y);
            a[x] = y;
        }
        work();
    }
}