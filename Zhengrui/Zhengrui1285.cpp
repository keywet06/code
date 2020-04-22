#include <bits/stdc++.h>
int a[500005], n;
int read() {
    int s = 0, t = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') t = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * t;
}
int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    for (int i = 1; i <= n; i++) {
        int tmp = 0;
        for (int j = 1; j <= n; j++) {
            tmp ^= (a[j] % (i + 1));
        }
        if (tmp) {
            printf("Alice ");
        } else {
            printf("Bob ");
        }
    }
    return 0;
}