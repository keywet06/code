#include <bits/stdc++.h>

using int64 = long long;

const int C = 26;

inline std::string reverse(std::string s) {
    std::string t;
    t.resize(s.size());
    for (int i = 0; i < s.size(); ++i) t[i] = s[s.size() - i - 1];
    return t;
}

inline int64 solve(std::string s) {
    struct node {
        int fail, len, ans;
        int son[C];
        node() { fail = len = ans = 0, memset(son, 0, sizeof(son)); }
        node(int _fail, int _len, int _ans)
            : fail(_fail), len(_len), ans(_ans) {
            memset(son, 0, sizeof(son));
        }
    };
    size_t n = s.length();
    std::vector<int> f, g;
    std::vector<node> vec;
    vec.emplace_back(0, -1, 0);
    vec.emplace_back(0, 0, 0);
    int o = 0;
    for (int i = 0; i < n; ++i) {
        int dir = s[i] - 'a';
        while (s[i - vec[o].len - 1] != s[i]) o = vec[o].fail;
        if (!vec[o].son[dir]) {
            int d = vec[o].fail;
            while (s[i - vec[d].len - 1] != s[i]) d = vec[d].fail;
            vec.emplace_back(std::max(vec[d].son[dir], 1), vec[o].len + 2,
                             vec[vec[d].son[dir]].ans);
            node &u = vec.back();
            u.ans +=
                u.len % 4 == 2 && u.len / 2 % (u.len - vec[u.fail].len) == 0;
            vec[o].son[dir] = vec.size() - 1;
        }
        f.push_back(vec[o = vec[o].son[dir]].ans);
        // std::cout << o;
    }
    // std::cout << '\n';
    // for (int i = 0; i < vec.size(); ++i) {
    //     std::cout << i << ": " << vec[i].fail << ' ' << vec[i].len << ' '
    //               << vec[i].ans << " {";
    //     int f = 0;
    //     for (int j = 0; j < C; ++j) {
    //         if (!vec[i].son[j]) continue;
    //         if (f) std::cout << ", ";
    //         f = 1, std::cout << char('a' + j) << ": " << vec[i].son[j];
    //     }
    //     std::cout << "};\n";
    // }
    std::string t = reverse(s);
    vec.clear();
    vec.emplace_back(0, -1, 0);
    vec.emplace_back(0, 0, 0);
    o = 0;
    for (int i = 0; i < n; ++i) {
        int dir = t[i] - 'a';
        while (t[i - vec[o].len - 1] != t[i]) o = vec[o].fail;
        if (!vec[o].son[dir]) {
            int d = vec[o].fail;
            while (t[i - vec[d].len - 1] != t[i]) d = vec[d].fail;
            vec.emplace_back(std::max(vec[d].son[dir], 1), vec[o].len + 2,
                             vec[vec[d].son[dir]].ans);
            node &u = vec.back();
            u.ans +=
                u.len % 2 == 0 && u.len / 2 % (u.len - vec[u.fail].len) == 0;
            vec[o].son[dir] = vec.size() - 1;
        }
        g.push_back(vec[o = vec[o].son[dir]].ans);
    }
    int64 ret = 0;
    for (int i = 1; i < n; ++i) ret += int64(f[i - 1]) * g[n - 1 - i];
    return ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int T;
    std::string s;
    std::cin >> T;
    while (T--) std::cin >> s, std::cout << solve(s) << '\n';
    return 0;
}