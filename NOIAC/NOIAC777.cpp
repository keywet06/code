#include <bits/stdc++.h>
const int N = 65;
class node {
   public:
    std::string s, rp, ed;
};
int n, now, j;
node s[N];
std::string ans, ns;
std::string l[N];
std::string rp(std::string);
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s[i].s;
        for (j = 0; j < s[i].s.length(); ++j) {
            s[i].rp = s[i].rp + s[i].s[j];
            if (rp(s[i].rp) < s[i].s) {
                break;
            }
        }
        for (j = 0; j < s[i].s.length(); ++j) {
            if (s[i].rp[j % s[i].rp.length()] != s[i].s[j]) {
                break;
            }
        }
        j = j / s[i].rp.length() * s[i].rp.length();
        for (; j < s[i].s.length(); ++j) {
            s[i].ed = s[i].ed + s[i].s[j];
        }
        s[i].rp = rp(s[i].rp);
        s[i].rp = s[i].rp.substr(0, 50);
        s[i].ed = s[i].ed + 'Z';
    }
    std::sort(s + 1, s + n + 1, [](node x, node y) {
        return x.rp != y.rp ? x.rp < y.rp : x.ed > y.ed;
    });
    ans = "";
    for (int i = n; i; --i) {
        ns = "Z";
        for (int j = 1; j <= s[i].s.length(); ++j) {
            ns = std::min(ns, s[i].s.substr(0, j) + ans);
        }
        ans = ns;
    }
    std::cout << ans << std::endl;
    return 0;
}
inline std::string rp(std::string x) {
    for (int i = 1; i <= 8; ++i) {
        x = x + x;
    }
    return x;
}