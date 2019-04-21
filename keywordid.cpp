#include <bits/stdc++.h>
#include <conio.h>
int main() {
    int k = 0;
    int c = getch();
    if (c == 3) {
        return 0;
    }
    printf("µ±Ç°×Ö·û¼üÅÌÂë£º");
    while (1) {
        for (int i = 1; i <= k; ++i) {
            printf("\b");
        }
        for (int i = 1; i <= k; ++i) {
            printf(" ");
        }
        for (int i = 1; i <= k; ++i) {
            printf("\b");
        }
        int s = 1;
        k = 0;
        while (s <= c) {
            s *= 10;
            ++k;
        }
        printf("%d", c);
        c = getch();
        if (c == 3) {
            return 0;
        }
    }
    return 0;
}