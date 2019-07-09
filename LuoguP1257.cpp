#include <bits/stdc++.h>
const int N = 10005;
double min;
double x[N], y[N];
int n;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    min = 1e30;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            min = std::min(min, sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])));
        }
    }
    printf("%.4f\n", min);
    return 0;
}