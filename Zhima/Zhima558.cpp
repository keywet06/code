#include <bits/stdc++.h>

const int B = 2;
const int N = 1005;

bool f, g;
bool a[B][N][N];

int n, lx, ly, c;
int x[N], y[N];

long long cnt;

inline int abs(int x) { return x < 0 ? -x : x; }

inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> x[i] >> y[i];
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            lx = x[i] - x[j], ly = y[i] - y[j];
            if (!ly) {
                if (g) continue;
                g = 1, ++cnt;
                continue;
            }
            f = lx * ly >= 0;
            c = gcd(lx = abs(lx), ly = abs(ly));
            lx /= c, ly /= c;
            if (a[f][lx][ly]) continue;
            a[f][lx][ly] = 1, ++cnt;
        }
    }
    std::cout << cnt << std::endl;
    return 0;
}