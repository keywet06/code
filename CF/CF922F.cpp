#include <bits/stdc++.h>

namespace oct {

void ios();

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int N = 300005;
bool del[N];
int n, k, cnt, limit, ans;
int val[N], prime[N];

void pre() {
    for (int i = 2; i <= n; i++) {
        if (!val[i]) prime[++cnt] = i;
        val[i]++;
        for (int j = i + i; j <= n; j += i) val[j]++;
    }
}

int main() {
    oct::ios();
    std::cin >> n >> k;
    pre();
    long long tot = 0;
    for (int i = 1; i <= n; i++) {
        tot += val[i];
        if (tot >= k) {
            ans = limit = i;
            break;
        }
    }
    if (tot > k) {
        for (int i = 1; i <= cnt; i++) {
            if (tot == k) break;
            if (tot - k >= limit / prime[i]) {
                del[prime[i]] = 1;
                tot -= limit / prime[i], ans--;
            }
        }
    }
    if (tot != k) {
        std::cout << "No" << std::endl;
    } else {
        std::cout << "Yes" << std::endl;
        std::cout << ans << std::endl;
        for (int i = 1; i <= limit; i++) {
            if (!del[i]) std::cout << i << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}