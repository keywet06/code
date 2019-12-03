#include <bits/stdc++.h>
int n, c, k, l, x;
std::map<int, int> is;
std::queue<int> queue;
int main() {
    scanf("%d %d %d", &n, &c, &k);
    l = c / k;
    is[0] = 1;
    queue.push(0);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &x);
        is[x] = 1;
        if (x < l) {
            queue.push(x);
        }
    }
    while (!queue.empty()) {
        int i = queue.front();
        queue.pop();
        x = 1;
        for (int j = i; j < c; j += l) {
            if (!is[j]) {
                x = 0;
                continue;
            }
        }
        if (x) {
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}