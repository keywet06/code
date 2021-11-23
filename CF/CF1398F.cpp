#include <bits/stdc++.h>

const int N = 1000005;
const uint R = 0xefffffff;

int n, ans, t;
int pre0[N], pre1[N], lst0[N], lst1[N];

std::string s;

std::mt19937 rd(std::chrono::system_clock::now().time_since_epoch().count());

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    std::cin >> s, s = ' ' + s;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '0') pre0[i] = lst0[i] = i;
        if (s[i] == '1') pre1[i] = lst1[i] = i;
        if (!lst0[i]) lst0[i] = lst0[i - 1];
        if (!lst1[i]) lst1[i] = lst1[i - 1];
    }
    pre0[n + 1] = pre1[n + 1] = 2 * n + 1;
    for (int i = n; i; --i) {
        if (!pre0[i]) pre0[i] = pre0[i + 1];
        if (!pre1[i]) pre1[i] = pre1[i + 1];
    }
    for (int k = 1; k <= n; ++k) {
        ans = 0;
        for (int i = 1; i + k - 1 <= n; i += k) {
            if (pre0[i] < i + k && pre1[i] < i + k) {
                i = std::min(lst1[i + k - 1], lst0[i + k - 1]) + 1 - k;
            } else {
                ++ans;
            }
        }
        std::cout << ans << " \n"[k == n];
    }
    return 0;
}