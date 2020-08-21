#include <bits/stdc++.h>
const int N = 305;
const int R = 49;
const int f[6][6] {
    {1, 0, 0, 1, 0, 1},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {1, 0, 1, 0, 0, 1}
};
int a[N + N][N + N];
int main() {
    freopen("B1.out", "w", stdout);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            a[i + N][j + N] = f[i][j];
        }
    }
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= i * 2 + 1; ++j) {
            a[N - 3 * i + 2 * j - 2][N - 3 * i + 0] = 1;
            a[N - 3 * i + 2 * j - 2][N - 3 * i + 2] = 1;
            a[N + 6 + 3 * i - 2 * j + 1][N + 6 + 3 * i - 3] = 1;
            a[N + 6 + 3 * i - 2 * j + 1][N + 6 + 3 * i - 1] = 1;
            a[N - 3 * i + 0][N + 6 + 3 * i - 2 * j + 1] = 1;
            a[N - 3 * i + 2][N + 6 + 3 * i - 2 * j + 1] = 1;
            a[N + 6 + 3 * i - 3][N - 3 * i + 2 * j - 2] = 1;
            a[N + 6 + 3 * i - 1][N - 3 * i + 2 * j - 2] = 1;
        }
        for (int j = 1; j <= i; ++j) {
            a[N + 6 + 3 * i - 3 - 2 * j][N - 3 * i + 0] = 1;
            a[N + 6 + 3 * i - 3 - 2 * j][N - 3 * i + 2] = 1;
            a[N - 3 * i + 2 * j + 2][N + 6 + 3 * i - 3] = 1;
            a[N - 3 * i + 2 * j + 2][N + 6 + 3 * i - 1] = 1;
        }
        for (int j = 1; j < i; ++j) {
            a[N - 3 * i + 0][N - 3 * i + 2 * j + 2] = 1;
            a[N - 3 * i + 2][N - 3 * i + 2 * j + 2] = 1;
            a[N + 6 + 3 * i - 3][N + 6 + 3 * i - 2 * j - 3] = 1;
            a[N + 6 + 3 * i - 1][N + 6 + 3 * i - 2 * j - 3] = 1;
        }
        a[N + 1 + i][N - 3 * i + 1] = 1;
        a[N + 4 - i][N + 6 + 3 * i - 2] = 1;
        a[N - 3 * i + 0][N + 3 - i] = 1;
        a[N - 3 * i + 1][N + 2 - i] = 1;
        a[N - 3 * i + 2][N + 3 - i] = 1;
        a[N + 6 + 3 * i - 3][N + 2 + i] = 1;
        a[N + 6 + 3 * i - 2][N + 3 + i] = 1;
        a[N + 6 + 3 * i - 1][N + 2 + i] = 1;
    }
    for (int i = N - 3 * R; i < N + 6 + 3 * R; ++i) {
        for (int j = N - 3 * R; j < N + 6 + 3 * R; ++j) {
            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}