#include <bits/stdc++.h>
const int N = 100005;
long long T, n, mod, x, y, z, w, c;
long long a[N], b[N];
int Main();
int main() {
    scanf("%lld %lld", &T, &mod);
    while (T--) {
        Main();
    }
    return 0;
}
inline int Main() {
    scanf("%lld", &n);
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        ++b[a[i]];
    }
    if (n <= 1000) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (j == k) {
                    continue;
                }
                int flag = 1;
                c = n;
                x = 0;
                y = a[j];
                z = a[k];
                --b[y];
                --b[z];
                (w = (z - y) - (y - x) + mod) %= mod;
                for (int l = 3; l <= n; ++l) {
                    if (!b[(x = z + z - y + w + mod) %= mod]) {
                        flag = 0;
                        c = l - 1;
                        break;
                    }
                    --b[x];
                    std::swap(x, y);
                    std::swap(y, z);
                }
                x = 0;
                y = a[j];
                z = a[k];
                ++b[y];
                ++b[z];
                for (int l = 3; l <= c; ++l) {
                    x = z + z - y + w + mod;
                    ++b[x];
                    std::swap(x, y);
                    std::swap(y, z);
                }
                if (flag) {
                    puts("Yes");
                    // printf("D: i = %d; j = %d; k = %d;\n", 0, j, k);
                    return 0;
                }
            }
        }
        puts("No");
    } else {
        for (int i = n; i; --i) {
            (a[i] -= a[i - 1] - mod) %= mod;
        }
        for (int i = n; i; --i) {
            (a[i] -= a[i - 1] - mod) %= mod;
        }
        for (int i = 4; i <= n; ++i) {
            if (a[i] != a[3]) {
                puts("No");
                return 0;
            }
        }
        puts("Yes");
    }
    return 0;
}