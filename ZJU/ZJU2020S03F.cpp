#include <bits/stdc++.h>
int n;
inline void sp(int n, int p, int s) {
    if (n == 1) {
        std::cout << p << " ";
        return;
    }
    int mid = n + s >> 1;
    sp(mid, p + s * (n >> 1), !s);
    sp(n - mid, p + (!s) * (n >> 1), !s);
}
int main() {
    std::cin >> n;
    sp(n, 1, 0);
    std::cout << std::endl;
    return 0;
}