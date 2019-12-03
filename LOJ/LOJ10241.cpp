#include <bits/stdc++.h>
int n, k;
int main() {
    scanf("%d %d", &n, &k);
    printf("%d\n", 2 - (bool)(n % (k + 1)));
    return 0;
}