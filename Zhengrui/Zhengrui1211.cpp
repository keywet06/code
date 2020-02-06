#include <bits/stdc++.h>
const int N = 50;
int cnt, n, l, r, mid;
long long sum;
long long a[N], b[N];
int check(int ans); 
int check(int ans) {
    for (int i = 1; i <= n; ++i) {
        b[i] = a[i] * ans;
    }
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[i]) {
            b[++cnt] = b[i];
        }
    }
    std::sort(b + 1, b + cnt + 1);
    for (int i = 1; i <= ans; ++i) {
        l = 0;
        for (int j = 2; j <= cnt; ++j) {
            if (b[j] + b[1] >= sum) {
                l = j;
                break;
            }
        }
        if (!l) {
            if (b[1] >= sum) {
                b[1] -= sum;
                if (!b[1]) {
                    for (int j = 1; j < cnt; ++j) {
                        b[j] = b[j + 1];
                    }
                    --cnt;
                }
                continue;
            }
            return 0;
        }
        b[l] -= sum - b[1];
        if (b[l]) {
            b[1] = b[l];
            for (int j = l; j < cnt; ++j) {
                b[j] = b[j + 1];
            }
            --cnt;
            l = 1;
            while (l < cnt && b[l] > b[l + 1]) {
                std::swap(b[l], b[l + 1]);
                ++l;
            }
        } else {
            for (int j = l; j < cnt; ++j) {
                b[j] = b[j + 1];
            }
            --cnt;
            for (int j = 1; j < cnt; ++j) {
                b[j] = b[j + 1];
            }
            --cnt;
        }
    }
    return 1;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        sum += a[i];
    }
    for (int i = 1; i <= 1000; ++i) {
        if (check(i)) {
            std::cout << i << std::endl;
            return 0;
        }
    }
    return 0;
}