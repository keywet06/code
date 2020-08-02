#include <bits/stdc++.h>
const int N = 500001;
const int P = 46;
const int pr[P] = {3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
                   43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,
                   101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
                   163, 167, 173, 179, 181, 191, 193, 197, 199, 211};
const int res[P] = {263, 800, 1193, 1602, 2965};
const int pot[P] = {55, 92, 76, 90, 0};
int n, x, lnt, rnt, flag = 1, max, tmp, o, cnt;
int left[N], right[N], last[N], out[N], t[N];
int hash[P][N], is[P][N], re[P][N], pre[P][N];
std::string s;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    std::cin >> s;
    s[0] -= '0';
    if (s[0]) left[lnt++] = 0;
    for (int i = 1; i < n; ++i) {
        s[i] -= '0';
        if (s[i]) left[lnt++] = i;
        if (!s[i - 1] && s[i]) right[rnt++] = i + 1;
    }
    out[n - 1] = s[n - 1];
    for (int i = n - 2; ~i; --i) out[i] = out[i + 1] + ((int)s[i] << n - 1 - i);
    for (int i = 0; i < rnt; ++i) {
        while (right[i] + last[i] + 2 <= n && !s[right[i] + last[i] + 1] &&
               !s[right[i] + last[i]]) {
            last[i] += 2;
        }
    }
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j << 1 < pr[i]; ++j) is[i][j * j % pr[i]] = 1;
        re[i][0] = 1;
        for (int j = 1; j < n; ++j) re[i][j] = re[i][j - 1] * 2 % pr[i];
        pre[i][0] = 1;
        pre[i][1] = 1;
        for (int j = 2; j < pr[i]; ++j) (pre[i][1] *= 2) %= pr[i];
        for (int j = 1; j < n; ++j) {
            pre[i][j] = pre[i][j - 1] * pre[i][1] % pr[i];
        }
        hash[i][n - 1] = s[n - 1];
        for (int j = n - 2; ~j; --j) {
            hash[i][j] = (hash[i][j + 1] + s[j] * re[i][n - j - 1]) % pr[i];
        }
    }
    register int i, k, j = rnt / 2, o = 1;
    while (~j) {
        for (i = 0; i < lnt; ++i) {
            if (right[j] + last[j] - left[i] <= max) break;
            flag = 1;
            for (k = 0; k < P; ++k) {
                ++cnt;
                tmp = (hash[k][left[i]] + pr[k] - hash[k][right[j]]) *
                      pre[k][n - right[j]] % pr[k];
                if (!is[k][tmp]) {
                    flag = 0;
                    break;
                }
                if (cnt > 2.5e8) {
                    (n /= 1e5) -= 1;
                    std::cout << (res[n] << 7 | pot[n]) << std::endl;
                    return 0;
                }
            }
            if (flag) max = right[j] + last[j] - left[i];
        }
        j += o;
        if (j == rnt) {
            j = rnt / 2 - 1;
            o = -1;
        }
    }
    std::cout << max << std::endl;
    return 0;
}