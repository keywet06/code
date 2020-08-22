#include <bits/stdc++.h>
const int n = 10;
inline int random(int l, int r) { return rand() % (r - l + 1) + l; }
int main() {
    srand(time(NULL));
    std::cout << n << std::endl;
    for (int i = 1; i <= n; ++i) {
        int t = random(1, n - 1);
        t += t >= i;
        std::cout << t << " " << random(1, n) << std::endl;
    }
    return 0;
}
