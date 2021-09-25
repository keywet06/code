#include <bits/stdc++.h>

using uint64 = unsigned long long;

const int E = 37;
const int R = 7;
const int N = int(5e5) + 5;

char s[N];

int n, ans, now, r;
int f[N];

uint64 hs[N], pre[N];

std::unordered_map<uint64, int> map;

inline uint64 hash(int l, int r) { return hs[r] - hs[l - 1] * pre[r - l + 1]; }

inline bool exist(int l, int r) { return map.count(hash(l, r)); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> s + 1, n = strlen(s + 1), pre[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] * E;
        hs[i] = s[i] - 'a' + R + hs[i - 1] * E;
    }
    map[0] = 1;
    for (int i = n; i >= 1; --i) {
        now = f[i + 1] + 1;
        while (!exist(i, i + now - 2) && !exist(i + 1, i + now - 1)) {
            for (int j = f[r = i + --now]; j; --j) {
                if (map[hash(r, r + j - 1)]++) break;
            }
        }
        ans = std::max(ans, f[i] = now);
    }
    std::cout << ans << std::endl;
    return 0;
}