#include <bits/stdc++.h>
int n, x, y;
int read();
void addedge(int, int);
int main() {
    n = read();
    for (int i = 1; i < n; ++i) {
        x = read();
        y = read();
        addedge(x, y);
    }
    return 0;
}
inline int read() {
    int x = 0, f = 1, ch = getchar();
    while (ch < '0' || '9' < ch) {
        f = (ch != '-') << 1 - 1;
        ch = getchar();
    }
    x = ch - '0';
    ch = getchar();
    while ('0' <= ch && ch <= '9') {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    ungetc(ch, stdin);
    return x * f;
}
