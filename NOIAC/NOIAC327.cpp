#include <bits/stdc++.h>
const int C = 20;
char cl[C], cr[C];
int T, lcl, lcr, x;
long long l, r;
void IntToChar(long long, char*);
int IsZero(char*, int);
void PrintZero(int);
int main() {
    scanf("%d", &T);
    while (T--) {
        memset(cl, 0, sizeof(cl));
        memset(cr, 0, sizeof(cr));
        scanf("%lld %lld", &l, &r);
        IntToChar(l, cl);
        IntToChar(r, cr);
        lcl = strlen(cl);
        lcr = strlen(cr);
        if (lcr - lcl) {
            if (cl[lcl - 1] < '5' || cl[lcl - 1] == '5' && IsZero(cl, lcl - 1)) {
                printf("5");
                PrintZero(lcl - 1);
            } else if (lcr - lcl > 1 || lcr - lcl == 1 && cr[lcr - 1] >= '5') {
                printf("5");
                PrintZero(lcl);
            } else if (lcr - lcl == 1) {
                if (IsZero(cl, lcl - 1)) {
                    printf("%lld", l);
                } else {
                    printf("%d", (cl[lcl - 1] ^ '0') + 1);
                    PrintZero(lcl - 1);
                }
            }
        } else {
            for (x = lcl - 1; ~x && cl[x] == cr[x]; --x) {
                printf("%c", cl[x]);
            }
            if (!~x) {
                printf("\n");
                continue;
            }
            if (IsZero(cl, x + 1)) {
                printf("0");
            } else if ((cl[x] < '5' || cl[x] == '5' && IsZero(cl, x)) && cr[x] >= '5') {
                printf("5");
            } else {
                printf("%c", cl[x] + !IsZero(cl, x));
            }
            PrintZero(x);
        }
        printf("\n");
    }
    return 0;
}
inline void IntToChar(long long x, char *str) {
    while (x) {
        *str = x % 10 ^ '0';
        x /= 10;
        ++str;
    }
    *str = 0;
}
inline int IsZero(char *str, int x) {
    for (int i = 0; i < x; ++i, ++str) {
        if (*str != '0') {
            return 0;
        }
    }
    return 1;
}
inline void PrintZero(int x) {
    while (x--) {
        printf("0");
    }
}