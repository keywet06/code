#include <bits/stdc++.h>
const int N = 100005;
int n, now, ntype, ps;
int a[N], p[N];
void die();
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    now = 0;
    ntype = 0;
    ps = 1;
    for (int i = 1; i <= n; ++i) {
        if (ntype == 0) {
            if (a[i] == 1 || a[i] == 0) {
                ++now;
                if (now > 9 || (ps == 1 && now > 8)) {
                    die();
                }
            }
        }
    }
    return 0;
}
inline void die() {
    printf("-1\n");
    exit(0);
}