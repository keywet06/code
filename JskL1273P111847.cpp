#include <bits/stdc++.h>
const int n_MAX = 100005;
int n, x, y;
int a[n_MAX], b[n_MAX];
int sum(int);
void updata(int);
int lowbit(int);
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &x, &y);
        ++x;
        ++b[sum(x)];
        updata(x);
    }
    for (int i = 0; i < n; ++i) printf("%d\n", b[i]);
    return 0;
}
inline int sum(int x) {
    int ans = 0;
    for (int i = x; i; i -= lowbit(i)) ans += a[i];
    return ans;
}
inline void updata(int x) {
    for (int i = x; i < n_MAX; i += lowbit(i)) ++a[i];
}
inline int lowbit(int x) { return x & (-x); }
