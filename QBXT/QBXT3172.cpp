#include <bits/stdc++.h>

const int N = 100005;

int c, n, s;
int a[N], Id[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> c;
    memset(Id, 255, sizeof(Id));
    Id[0] = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (Id[s = (s + a[i]) % c] >= 0) {
            std::cout << i - Id[s] << '\n';
            for (int j = Id[s] + 1; j <= i; ++j) {
                std::cout << j << " \n"[j == i];
            }
            break;
        }
        Id[s] = i;
    }
    return 0;
}