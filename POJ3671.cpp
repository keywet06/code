#include <cstdio>
char ch;
int as, ax, ay, n, x, y;
int a[1000001], l = 500000, r = 499999;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        getchar();
        --l;
        a[l] = getchar();
    }
    ++n;
    while (--n) {
        ++as;
        if (a[l] < a[r]) {
            printf("%c", a[l]);
            ++l;
        } else if (a[l] > a[r]) {
            printf("%c", a[r]);
            --r;
        } else {
            x = l;
            y = r;
            ax = 0;
            while (x <= r) {
                if (a[x] != a[y]) {
                    ax = 1;
                    break;
                }
                ++x;
                --y;
            }
            if (ax) {
                if (a[x] < a[y]) {
                    printf("%c", a[l]);
                    ++l;
                } else {
                    printf("%c", a[r]);
                    --r;
                }
            } else {
                printf("%c", a[l]);
                ++l;
            }
        }
        // if (a > 5) break;
        if (as % 80 == 0) {
            puts("");
        }
        // printf("\nDebug: a = {'%c'", a[l]);
        // for (int i = l + 1; i <= r; ++i) {
        // 	printf(", '%c'", a[i]);
        // }
        // printf("};\n");
    }
    return 0;
}
