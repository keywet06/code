#include <bits/stdc++.h>
const int N = 100005;
int n, T, C, opt, c, a, l, r, ans, tot;
int str[N], sl[N], sr[N], slast[N];
std::vector<int> now;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> T >> C;
    while (n--) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> c;
            c = (c - 1 + ans * T) % C + 1;
            now.push_back(c);
        } else {
            std::cin >> a >> l >> r;
            a = (a + ans * T) % (tot + 1);
            l = (l - 1 + ans * T) % now.size();
            r = (r - 1 + ans * T) % now.size();
            if (l > r) {
                std::swap(l, r);
            }
            if (opt == 2) {
                ++tot;
                sl[tot] = l;
                sr[tot] = r;
                slast[tot] = a;
            } else {
                ans = 0;
                while (a) {
                    c = std::min(sr[a] - sl[a], r - l);
                    for (opt = 0; opt <= c; ++opt) {
                        if (now[sl[a] + opt] != now[l + opt]) {
                            break;
                        }
                    }
                    ans = std::max(ans, opt);
                    a = slast[a];
                }
                std::cout << ans << "\n";
            }
        }
    }
    return 0;
}