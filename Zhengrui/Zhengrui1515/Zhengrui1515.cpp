#include <bits/stdc++.h>
const int N = 400;
int n;
int a[N][N];
int main() {
    for (int i = 1; i < N; i += 2) {
        for (int j = 1; j < N; j += 2) a[i][j] = 1;
    }
    for (int i = 4; i < N; i += 4) {
        for (int j = 4; j < N; j += 4) a[i][j] = 1;
    }
    for (int i = 6; i < N; i += 8) {
        for (int j = 6; j < N; j += 8) a[i][j] = 1;
    }
    for (int i = 10; i < N; i += 16) {
        for (int j = 10; j < N; j += 16) a[i][j] = 1;
    }
    for (int i = 18; i < N; i += 32) {
        for (int j = 18; j < N; j += 32) a[i][j] = 1;
    }
    for (int i = 34; i < N; i += 64) {
        for (int j = 34; j < N; j += 64) a[i][j] = 1;
    }
    for (int i = 66; i < N; i += 128) {
        for (int j = 66; j < N; j += 128) a[i][j] = 1;
    }
    for (int i = 130; i < N; i += 256) {
        for (int j = 130; j < N; j += 256) a[i][j] = 1;
    }
    for (int i = 258; i < N; i += 512) {
        for (int j = 258; j < N; j += 512) a[i][j] = 1;
    }
    std::cin >> n;
    if (n & 1) {
        for (int i = 1; i <= n; ++i) a[i][n - 1] = a[n - 1][i] = 0;
    } else {
        for (int i = 1; i < n; ++i) a[i][n] = a[n][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}