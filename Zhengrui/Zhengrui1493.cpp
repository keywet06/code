#include <bits/stdc++.h>
const int K = 10;
const int N = 105000;
int n, k;
int put[K], a[K], b[K];
int hq[N];
int p[K][N];
long long ans;
inline int check(int left, int right, int xb) {
    for (int i = 1; i <= k; ++i) b[i] = put[i];
    for (int i = left; i <= right; ++i) {
        bool flag2 = 0;
        for (int j = 1; j <= k; ++j) {
            if (p[j][i] == b[j]) {
                flag2 = 1;
                break;
            }
        }
        if (!flag2) {
            if (xb >= k) return i - 1;
            ++xb;
            b[a[xb]] = p[a[xb]][i];
        }
    }
    return right;
}
inline void solve(int left, int right) {
    if (hq[left] >= right) return;
    if (right - left + 1 <= k) {
        for (int i = left; i <= right; ++i) hq[i] = std::max(hq[i], right);
        return;
    }
    int mid = left + right >> 1;
    for (int i = 1; i <= k; ++i) a[i] = i;
    do {
        memset(put, -1, sizeof(put));
        int ls = mid, xb = 0;
        bool flag1 = 0;
        for (int i = mid, ls = mid; i >= left; --i) {
            bool flag2 = 0;
            for (int j = 1; j <= k; ++j)
                if (p[j][i] == put[j]) {
                    flag2 = 1;
                    break;
                }
            if (!flag2) {
                int tmp = check(mid + 1, right, xb);
                for (int j = i + 1; j <= ls; ++j) hq[j] = std::max(hq[j], tmp);
                if (xb >= k) {
                    flag1 = 1;
                    break;
                }
                ++xb;
                put[a[xb]] = p[a[xb]][i];
                ls = i;
            }
        }
        if (!flag1) {
            int tmp = check(mid + 1, right, xb);
            for (int j = left; j <= ls; ++j) hq[j] = std::max(hq[j], tmp);
        }
    } while (std::next_permutation(a + 1, a + k + 1));
    solve(left, mid);
    solve(mid + 1, right);
}
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            std::cin >> p[j][i];
        }
    }
    solve(1, n);
    for (int i = 1; i <= n; ++i) {
        ans = (ans + (hq[i] - i + 1) * 1LL * (hq[i] - i + 2) / 2);
    }
    std::cout << ans << std::endl;
    return 0;
}