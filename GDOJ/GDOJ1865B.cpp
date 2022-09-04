#include <bits/stdc++.h>

using int64 = long long;

int k;

struct node {
    int fail, len;
    std::vector<int> next;
    node() : fail(0), len(0), next(k) {}
    node &operator()();
    node &operator()(int x);
    int &operator[](int x);
};

const int N = 1000005;
const int M = N << 1;

node nd[M];

node &node::operator()() { return nd[fail]; }
node &node::operator()(int x) { return nd[next[x]]; }
int &node::operator[](int x) { return next[x]; }

int Main(int n, char *s) {
    int cnt = 0, last = 0, p = 0, q = 0, cur = 0, clo = 0;
    int64 ans = 0;
    for (int i = 0; i < n * 2 + 5; ++i) nd[i] = node();
    last = ++cnt;
    for (int i = 0; i < n; ++i) {
        nd[cur = ++cnt].len = nd[p = last].len + 1;
        while (p && !nd[p][s[i]]) nd[p][s[i]] = cur, p = nd[p].fail;
        if ((q = nd[p][s[i]], !p) && (nd[cur].fail = 1)) continue;
        if (nd[p].len + 1 == nd[q].len && (nd[cur].fail = q)) continue;
        nd[clo = ++cnt] = nd[q], nd[clo].len = nd[p].len + 1;
        while (p && nd[p][s[i]] == q) nd[p][s[i]] = clo, p = nd[p].fail;
        nd[q].fail = nd[cur].fail = clo;
    }
    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, P;
    std::cin >> n >> k >> P;
    char s[n + 5];
    int Ans = 0;
    memset(s, 0, sizeof(s));
    while (!s[n]) {
        Ans += Main(n, s);
        for (int i = (++s[0], 0); i < n && s[i] == k; ++i) s[i] = 0, ++s[i + 1];
    }
    std::cout << Ans % P << std::endl;
    return 0;
}