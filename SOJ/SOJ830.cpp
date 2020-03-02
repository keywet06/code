#include <bits/stdc++.h>
const int N = 100;
const int Np = 105;
int n, max, maxa, maxb, as;
int s[Np], p[Np], q[Np];
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s[i] >> p[i];
    }
    for (int i = 1; i * 2 <= n; ++i) {
        maxa = maxb = 0;
        max = -1e9;
        for (int j = 1; j <= n; ++j) {
            if (q[j]) {
                continue;
            }
            for (int k = 1; k <= n; ++k) {
                if (q[k] || s[j] < s[k] || j == k) {
                    continue;
                }
                if (p[j] - p[k] > max) {
                    max = p[j] - p[k];
                    maxa = j;
                    maxb = k;
                }
            }
        }
        q[maxa] = 1;
        q[maxb] = 1;
        as += max;
        std::cout << as << std::endl;
    }
    return 0;
}