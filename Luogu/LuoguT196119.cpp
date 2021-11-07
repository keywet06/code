#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

const int C = 26;
const int HB = 17;
const int HC = 47;
const int HD = 191153174;
const int HP = 998244353;

inline std::string append(const std::string s) {
    std::string ret;
    for (char ch : s) ret.push_back('#'), ret.push_back(ch);
    return ret.push_back('#'), ret;
}

inline int solve(const std::string s) {
    struct node {
        int fail, len, ans, id;
        int son[C];
        node() { fail = len = ans = id = 0, memset(son, 0, sizeof(son)); }
        node(int _fail, int _len, int _ans)
            : fail(_fail), len(_len), ans(_ans) {
            memset(son, id = 0, sizeof(son));
        }
    };
    int n = s.size();
    std::vector<int> mf, hs, re, pr;
    std::vector<node> vec;
    std::unordered_map<int, int> map;
    auto hasha = [&hs, &pr](int l, int r) {
        return int(
            (hs[r] + HP - int64(l ? hs[l - 1] : 0) * pr[r - l + 1] % HP) % HP);
    };
    auto hashb = [&hs, &pr](int l, int r) {
        return int(
            (hs[r] + HP -
             int64((l ? hs[l - 1] : 0) - (HB - 1)) * pr[r - l + 1] % HP) %
            HP);
    };
    hs.push_back(s[0] - 'a' + HB), re.push_back(1), pr.push_back(1);
    for (int i = 1; i < n; ++i) {
        hs.push_back((int64(hs.back()) * HC + HB + s[i] - 'a') % HP);
        re.push_back(int64(re.back()) * HD % HP);
        pr.push_back(int64(pr.back()) * HC % HP);
    }
    re.push_back(int64(re.back()) * HD % HP);
    pr.push_back(int64(pr.back()) * HC % HP);
    vec.emplace_back(0, -1, 0);
    vec.emplace_back(0, 0, 0);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        int dir = s[i] - 'a';
        while (s[i - vec[cur].len - 1] != s[i]) cur = vec[cur].fail;
        if (vec[cur].son[dir] && (cur = vec[cur].son[dir])) continue;
        int fal = vec[cur].fail;
        while (s[i - vec[fal].len - 1] != s[i]) fal = vec[fal].fail;
        vec.emplace_back(std::max(vec[fal].son[dir], 1), vec[cur].len + 2, 0);
        cur = vec[cur].son[dir] = vec.size() - 1;
    }
    std::string t = append(s);
    int ce = -1, le = 0, m = t.length();
    for (int i = (mf.resize(m), 0); i < m; ++i) {
        cur = i <= ce + le ? std::min(ce + le - i, mf[ce * 2 - i]) : 0;
        while (i - cur >= 0 && i + cur < m && t[i - cur] == t[i + cur]) ++cur;
        if (i + (mf[i] = --cur) > ce + le) ce = i, le = mf[i];
    }
    vec[0].id = HB - 1;
    for (int i = 0; i < vec.size(); ++i) {
        map[vec[i].id] = i;
        for (int j = 0; j < C; ++j) {
            if (!vec[i].son[j]) continue;
            vec[vec[i].son[j]].id = (int64(vec[i].id) * HC + HB + j) % HP;
        }
    }
    for (int i = 0; i < n; ++i) {
        cur = mf[i << 1 | 1] >> 1;
        vec[map[hashb(i, i + cur)]].ans ^= i;
    }
    for (int i = 1; i < n; ++i) {
        cur = mf[i << 1] >> 1;
        vec[map[hasha(i, i + cur - 1)]].ans ^= i - 1;
    }
    int ret = 0;
    for (int i = vec.size() - 1; i > 1; --i) {
        for (int j = 0; j < C; ++j) {
            if (!vec[i].son[j]) continue;
            vec[i].ans ^= vec[vec[i].son[j]].ans;
        }
        ret = std::max(ret, vec[i].ans);
    }
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