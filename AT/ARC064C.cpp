#include <bits/stdc++.h>

using int64 = long long;

const int N = 1005;

double min;
double dis[N];

int n, p;
int px[N], py[N], used[N], pr[N];

int64 sqr(int64 x) { return x * x; }

double d(int x, int y) {
    return std::max(
        sqrt(sqr(px[x] - px[y]) + sqr(py[x] - py[y])) - pr[x] - pr[y], 0.0);
}

int main() {
    std::cin >> px[1] >> py[1] >> px[2] >> py[2];
    std::cin >> n;
    for (int i = 3; i <= n + 2; ++i) std::cin >> px[i] >> py[i] >> pr[i];
    n += 2;
    for (int i = 1; i <= n; ++i) dis[i] = 1e100;
    dis[1] = 0;
    for (int i = 1; i <= n; ++i) {
        min = 1e100;
        for (int j = 1; j <= n; ++j) {
            if (!used[j] && dis[j] < min) min = dis[p = j];
        }
        used[p] = 1;
        for (int j = 1; j <= n; ++j) dis[j] = std::min(dis[j], dis[p] + d(p, j));
    }
    std::cout << std::showpoint << std::setprecision(10) << std::fixed;
    std::cout << dis[2] << std::endl;
    return 0;
}