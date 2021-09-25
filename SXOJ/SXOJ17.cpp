#include <bits/stdc++.h>

using uint64 = unsigned long long;

const int E = 37;
const int N = 1000005;

int T, n, l, r, mid;

uint64 hs[N], pre[N];

std::string s;

std::unordered_set<uint64> set;

inline uint64 hash(int l, int r) { return hs[r] - hs[l - 1] * pre[r - l + 1]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> s, n = s.length(), s = ' ' + s, pre[0] = 1;
        for (int i = 1; i <= n; ++i) {
            hs[i] = hs[i - 1] * E + s[i];
            pre[i] = pre[i - 1] * E;
        }
        set.clear(), set.insert(0);
        for (int i = 1; i <= n >> 1; ++i) {
            l = 0, r = i;
            while (l < r) {
                mid = l + r + 1 >> 1;
                if (hash(1, mid) == hash(i + 1, i + mid)) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            if (hash(l + 1, i) == hash(n - i + l + 1, n)) {
                set.insert(hash(1, i));
            }
            l = 0, r = i;
            while (l < r) {
                mid = l + r + 1 >> 1;
                if (hash(1, mid) == hash(n - i + 1, n - i + mid)) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            if (hash(n - i + l + 1, n) == hash(n - i - i + l + 1, n - i)) {
                set.insert(hash(n - i + 1, n));
            }
        }
        std::cout << set.size() << '\n';
    }
    return 0;
}