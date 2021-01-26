#include <bits/stdc++.h>

const int N = 55;
const int M = 405;
const int Z = 820005;

int n, m, k;
int h[N], p[N];
int ax[Z], ay[Z];
int a[N][M];

void mova(int x, int y) { ax[++k] = x, ay[k] = y, a[y][++h[y]] = a[x][h[x]--]; }

void move(int x, int y) { mova(p[x], p[y]); }

void swap(int x, int y) { std::swap(p[x], p[y]); }

void move(int x, int y, int t) {
    while (t--) move(x, y);
}

int getnum(int x, int d) {
    int num = 0;
    for (int i = 1; i <= m; ++i) num += a[p[x]][i] == d;
    return num;
}

void split(int x, int y, int z, int d) {
    for (int i = m; i; --i) move(x, a[p[x]][i] == d && h[p[y]] <= m ? y : z);
}

void make0() {
    int num = getnum(1, n);
    move(1, n + 1, num);
    split(1, n, n + 1, n);
    move(n + 1, 1, m - num);
    split(2, n + 1, 1, n);
    swap(1, n), swap(2, n + 1);
}

int fit(int x) { return (x - 1) % (n + 1) + 1; }

void make1() {
    make0();
    for (int i = 1; i <= n + 1; ++i) {
        int num = getnum(i, n);
        move(fit(n + i - 1), fit(n + i), num);
        split(fit(i), fit(n + i - 1), fit(n + i), n);
    }
    for (int i = 1; i < n; ++i) {
        int num = getnum(i, n);
        move(1, n + 1, num);
        move(n, 1, num);
    }
    swap(1, n);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) std::cin >> a[i][j];
        h[i] = m, p[i] = i;
    }
    p[n + 1] = n + 1;
    for (n = n; n > 2; --n) make1();
    int num = getnum(1, 1);
    move(2, 3, num);
    split(1, 2, 3, 1);
    move(2, 1, num);
    move(3, 1, m - num);
    move(3, 2, num);
    move(1, 3, m - num);
    split(2, 1, 3, 1);
    std::cout << k << '\n';
    for (int i = 1; i <= k; ++i) std::cout << ax[i] << ' ' << ay[i] << '\n';
    return 0;
}