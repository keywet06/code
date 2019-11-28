#include "Octinc/PersistentArray.hpp"
const int N = 1000005;
Octinc::PersistentArray<int, N> a;
int m, n, x, y, z;
int version[N];
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    version[0] = a.getVersion();
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &z, &x);
        z = version[z];
        if (x == 1) {
            scanf("%d %d", &x, &y);
            a(z, x) = y;
        } else {
            scanf("%d", &x);
            printf("%d\n", a(z, x));
        }
        version[i] = a.getVersion();
    }
    return 0;
}