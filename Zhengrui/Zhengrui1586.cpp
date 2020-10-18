#include <bits/stdc++.h>

const int C = 10;

char cnt;
char buff[C];
int n, k;

inline void write(int x) {
    if (!x) return putchar(48), putchar(32), void(0);
    while (x) buff[++cnt] = x % 10 + '0', x /= 10;
    for (; cnt; --cnt) putchar(buff[cnt]);
    putchar(32);
}

int main() {
    std::cin >> n >> k, k = n / 4;
    if (n % 4 == 3) {
        for (int i = 0; i < n; ++i) write(i);
        putchar(10);
        for (int i = 0; i <= n / 2; ++i) write(n - i - 1);
        for (int i = n / 2 + 1; i < n - 1; ++i) write(n - i - 2);
        write(n - (n / 2) - 2);
        putchar(10);
        return 0;
    } else if (n % 4 == 2) {
        for (int i = 0; i < n; ++i) write(i);
        putchar(10);
        for (int i = 0; i < n / 2; ++i) write(n - i - 1);
        for (int i = n / 2; i < n - 1; ++i) write(n - i - 2);
        write(n - (n / 2) - 1);
        putchar(10);
        return 0;
    } else if (n % 4 == 1) {
        for (int i = 0; i < n; ++i) write(i);
        putchar(10);
        for (int i = 0; i < k; ++i) write(n - i - 1);
        write(k);
        for (int i = k + 1; i <= 2 * k; ++i) write(n - i);
        write(0);
        for (int i = 2 * k + 2; i < 3 * k + 2; ++i) write(n - i + 1);
        for (int i = 3 * k + 2; i < n; ++i) write(n - i);
        putchar(10);
    } else {
        for (int i = 0; i < n; ++i) write(i);
        putchar(10);
        for (int i = 0; i < k; ++i) write(n - i - 1);
        write(k);
        for (int i = k + 1; i < k * 2; ++i) write(n - i);
        write(0);
        for (int i = 2 * k + 1; i <= 3 * k; ++i) write(n - i + 1);
        for (int i = 3 * k + 1; i < n; ++i) write(n - i);
        putchar(10);
    }
    return 0;
}