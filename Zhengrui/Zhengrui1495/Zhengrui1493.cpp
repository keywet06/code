#include <bits/stdc++.h>
const int N = 5005;
const int L = 5;
int n, K, p, px, py;
int a[N][L];
long long ans;
inline void extend(int i) {
    while (i - p && (px == a[i - p][0] || py == a[i - p][1] || !~px || !~py)) {
        if (px != a[i - p][0] && py != a[i - p][1]) {
            if (!~px) {
                px = a[i - p][0];
            } else {
                py = a[i - p][1];
            }
        }
        ++p;
    }
}
inline void refactor(int i) {
    if (a[i][0] != a[i - 1][0] && a[i][1] != a[i - 1][1]) {  
        px = a[i][0];
        py = a[i - 1][1];
        if (px != a[i - 2][0] && py != a[i - 2][1]) {
            px = a[i - 1][0];
            py = a[i][1];
        }
    } else if (a[i][0] == a[i - 1][0]) {
        px = a[i][0];
        py = -1;
    } else {
        px = -1;
        py = a[i][1];
    }
    extend(i);
}
int main() {
    std::cin >> n >> K;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < K; ++j) {
            std::cin >> a[i][j];
        }
    }
    a[0][0] = a[0][1] = -2;
    if (K == 1) {
        for (int i = 1; i <= n; ++i) {
            ans += p = a[i][0] == a[i - 1][0] ? p + 1 : 1;
        }
        std::cout << ans << std::endl;
    } else if (K == 2) {
        p = 2;
        ans = 4;
        for (int i = 3; i <= n; ++i) {
            if (p == 2) {
                refactor(i);
            } else {
                if (px == a[i][0] || py == a[i][1] || !~px || !~py) {
                    ++p;
                    if (px != a[i][0] && py != a[i][1]) {
                        if (!~px) {
                            px = a[i][0];
                        } else {
                            py = a[i][1];
                        }
                    }
                } else {
                    refactor(i);
                }
            }
            ans += p * (p + 1) / 2;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}