#include <bits/stdc++.h>
const int N = 100005;
class pairs {
    public:
        int id;
        int o[3];
};
int ans, n, max, min, x;
pairs a[N];
int cmp(pairs, pairs);
int operator == (pairs, pairs);
int main() {
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        a[i].id = i;
        a[i].o[0] = a[i - 1].o[0] + (x == 0);
        a[i].o[1] = a[i - 1].o[1] + (x == 1);
        a[i].o[2] = a[i - 1].o[2] + (x == 2);
        if (x = std::min(a[i].o[0], std::min(a[i].o[1], a[i].o[2]))) {
            a[i].o[0] -= x;
            a[i].o[1] -= x;
            a[i].o[2] -= x;
        }
    }
    std::sort(a, a + n + 1, cmp);
    max = 0;
    min = n + 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == a[i + 1]) {
            max = std::max(max, a[i].id);
            max = std::max(max, a[i + 1].id);
            min = std::min(min, a[i].id);
            min = std::min(min, a[i + 1].id);
            ans = std::max(ans, max - min);
        } else {
            max = 0;
            min = n + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
inline int cmp(pairs x, pairs y) {
    if (x.o[0] != y.o[0]) {
        return x.o[0] < y.o[0];
    }
    if (x.o[1] != y.o[1]) {
        return x.o[1] < y.o[1];
    }
    if (x.o[2] != y.o[2]) {
        return x.o[2] < y.o[2];
    }
    return x.id < y.id;
}
inline int operator == (pairs x, pairs y) {
    return x.o[0] == y.o[0] && x.o[1] == y.o[1] && x.o[2] == y.o[2];
}