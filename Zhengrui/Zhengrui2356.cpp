#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a), _ = int(b); i <= _; ++i)
#define per(i, a, b) for (int i = int(a), _ = int(b); i >= _; --i)
using namespace std;
typedef long long ll;
const ll inf = ll(1e15) + 1;
struct node {
    int len;
    ll cnt;
    node(int len = 0, ll cnt = 1) : len(len), cnt(cnt) {}
    node F() { return node{len + 1, cnt}; }
    node operator+(node o) {
        if (len == o.len) return node{len, min(inf, cnt + o.cnt)};
        return len > o.len ? *this : o;
    }
};
const int N = 1e4 + 10;
int n, m, a[N][2], b[N][2];
char s[N], t[N];
node dp[3][N];
void init(char *s, int a[N][2], int &n) {
    n = strlen(s + 1);
    rep(i, 1, n) {
        rep(j, 0, 1) a[i][j] = a[i - 1][j];
        a[i][s[i] - '0'] = i;
    }
}
int main() {
    scanf("%s%s", s + 1, t + 1);
    init(s, a, n);
    init(t, b, m);
    rep(i, 1, n) {
        rep(j, 0, m) dp[s[i] - '0'][j] = dp[2][j], dp[2][j] = node();
        rep(k, 0, 1) if (a[i][k]) rep(j, 1, m) if (b[j][k]) dp[2][j] = dp[2][j] + dp[k][b[j][k] - 1].F();
    }
    cout << "cnt=" << dp[2][m].cnt << ",len=" << dp[2][m].len << endl;
    return 0;
}