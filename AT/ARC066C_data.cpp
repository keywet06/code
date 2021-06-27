#include <bits/stdc++.h>

int n = 8, maxa = 10;

char putr() { return rand() & 1 ? '+' : '-'; }
int puti() { return rand() % maxa + 1; }

int main() {
    srand(time(NULL));
    std::cout << n << std::endl;
    std::cout << puti();
    for (int i = 2; i <= n; ++i) {
        std::cout << ' ' << putr() << ' ' << puti();
    }
    std::cout << std::endl;
    return 0;
}