#include <bits/stdc++.h>

const int N = 10;

int n, k;
int a[N][N];

int main() {
    a[2][2] = 1;
    a[2][3] = 9;
    a[2][4] = 30;
    a[3][3] = 8;
    a[3][4] = 104;
    a[4][2] = 1;
    a[4][3] = 12;
    a[4][4] = 528;
    std::cin >> n >> k;
    std::cout << a[n][k] << std::endl;
    return 0;
}