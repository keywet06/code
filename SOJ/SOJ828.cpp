#include <bits/stdc++.h>
const int N = 3000005;
char str[N];
int n, q, t, ans, opt, as, len;
int next[N];
std::string now;
inline int decode(char* s, int T, int lans) {
    if (T == 0) return strlen(s);
    int L = strlen(s);
    for (int i = 0; i < L; ++i) s[i] = (s[i] - 'a' + lans) % 26 + 'a';
    for (int i = 0; i < L; ++i) {
        lans = ((long long)lans * 131 + i) % L;
        std::swap(s[i], s[lans]);
    }
    return L;
}
int main() {
    std::cin >> n >> q >> t;
    std::cin >> now;
    next[0] = -1;
    for (int i = 1; i <= q; ++i) {
        std::cin >> opt >> str;
        len = decode(str, t, ans);
        if (opt == 1) {
            now = now + str;
        } else if (opt == 2) {
            now = str + now;
        } else if (opt == 3) {
            for (int i = 1; i < len; ++i) {
                next[i] = next[i - 1];
                while (~next[i] && str[next[i] + 1] != str[i])
                    next[i] = next[next[i]];
                next[i] += str[next[i] + 1] == str[i];
            }
            as = -1;
            ans = 0;
            for (int i = 0; i < now.size(); ++i) {
                while (~as && str[as + 1] != now[i]) as = next[as];
                as += str[as + 1] == now[i];
                if (as + 1 == len) {
                    as = next[as];
                    ++ans;
                }
            }
            std::cout << ans << "\n";
        }
    }
    return 0;
}