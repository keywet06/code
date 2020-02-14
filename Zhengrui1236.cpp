#include <bits/stdc++.h>
const int N = 510;
const int mo = 998244353;
int n, ans, a[N];
char bg[N][N], bf[N][N];
inline int power(int a, int b) {
    int ans = 1;
    for (; b >= 1; b >>= 1, a = 1ll * a * a % mo) {
        if (b & 1) {
            ans = 1ll * ans * a % mo;
        }
    }
    return ans;
}
namespace matt {

int bg[N][N], d[N][N], a[N][N], inv[N], n;
inline void calc(int n) {
    matt::n = n;
    for (int i = 1; i <= n; i++) {
        std::fill(bg[i], bg[i] + n + 1, 0);
    }
    for (int i = 1; i <= n; i++) {
        std::fill(d[i], d[i] + n + 1, 0);
    }
}
void insert(int u, int v) {
    d[u][u]++;
    d[v][v]++;
    bg[u][v] = bg[v][u] = bg[v][u] + 1;
}
int kmain() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = (d[i][j] - bg[i][j] + mo) % mo;
        }
    }
    int sign = 1;
    for (int i = 1; i < n; i++) {
        int j = 0;
        for (int k = i; k < n; k++) {
            if (a[k][i]) {
                j = k;
                break;
            }
        }
        if (i != j) {
            for (int k = i; k < n; k++) {
                std::swap(a[i][k], a[j][k]);
            }
            sign *= -1;
        }
        inv[i] = power(a[i][i], mo - 2);
        for (j = i + 1; j < n; j++) {
            int d = 1ll * a[j][i] * inv[i] % mo;
            for (int k = i; k < n; k++) {
                (a[j][k] += mo - 1ll * d * a[i][k] % mo) %= mo;
            }
        }
    }
    int ans = 1;
    for (int i = 1; i < n; i++) {
        ans = 1ll * ans * a[i][i] % mo;
    }
    return sign == 1 ? ans : (mo - ans) % mo;
}

}  // namespace matt
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    if (n == 1) {
        std::cout << 0 << std::endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> bg[i] + 1;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> bf[i] + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            if (bf[i][j] == '1' && bg[i][j] == '1') {
                matt::calc(n - 1);
                for (int u = 1; u <= n; u++) {
                    for (int v = u + 1; v <= n; v++) {
                        if (bg[u][v] == '1' && !(u == i && v == j)) {
                            int x = u == j ? i : (u > j ? u - 1 : u);
                            int y = v == j ? i : (v > j ? v - 1 : v);
                            matt::insert(x, y);
                        }
                    }
                }
                (ans += matt::kmain()) %= mo;
            }
    }
    std::cout << ans % mo << std::endl;
    return 0;
}