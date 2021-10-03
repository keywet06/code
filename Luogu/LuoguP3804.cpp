#include <bits/stdc++.h>

using int64 = long long;

const int C = 26;

struct node {
    int fail, len;
    int next[C];
    node &operator()();
    node &operator()(int x);
    int &operator[](int x);
};

const int N = 1000005;
const int M = N << 1;

char s[N];

int cnt, n, last, p, q, cur, clo;
int count[N];
int size[M], rep[M];

int64 ans;

node nd[M];

node &node::operator()() { return nd[fail]; }
node &node::operator()(int x) { return nd[next[x]]; }
int &node::operator[](int x) { return next[x]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> s, n = strlen(s);
    for (int i = 0; i < n; ++i) s[i] -= 'a';
    last = ++cnt;
    for (int i = 0; i < n; ++i) {
        nd[cur = ++cnt].len = nd[p = last].len + 1, size[last = cur] = 1;
        while (p && !nd[p][s[i]]) nd[p][s[i]] = cur, p = nd[p].fail;
        if ((q = nd[p][s[i]], !p) && (nd[cur].fail = 1)) continue;
        if (nd[p].len + 1 == nd[q].len && (nd[cur].fail = q)) continue;
        nd[clo = ++cnt] = nd[q], nd[clo].len = nd[p].len + 1;
        while (p && nd[p][s[i]] == q) nd[p][s[i]] = clo, p = nd[p].fail;
        nd[q].fail = nd[cur].fail = clo;
    }
    for (int i = 1; i <= cnt; ++i) ++count[nd[i].len];
    for (int i = 1; i <= n; ++i) count[i] += count[i - 1];
    for (int i = 1; i <= cnt; ++i) rep[count[nd[i].len]--] = i;
    for (int i = cnt; i; --i) {
        if (size[nd[rep[i]].fail] += size[rep[i]], size[rep[i]] <= 1) continue;
        ans = std::max(ans, int64(size[rep[i]]) * nd[rep[i]].len);
    }
    std::cout << ans << std::endl;
    return 0;
}