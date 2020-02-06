#include <bits/stdc++.h>
#define okline() (std::cerr << "Debug: " << __FILE__ << ":" << __LINE__ << \
  std::endl)
const int K = 2;
const int LKa = 29;
const int N = 100000;
const int Np = N + 5;
const int N_timesLKa = N * LKa;
const int N_timesLKap = N_timesLKa + 5;
const int N_1 = 1000;
const int N_1p = N_1 + 5;
int cnt, tp, tp2, n, q, tag1, tag2, tag3, tag4, ans;
int w[Np], fa[Np], opt[Np], op1[Np], op2[Np], tans[Np];
int tfa[N_timesLKap];
int son[N_timesLKap][K];
std::vector<int> to[Np];
void dfs(int u) {
    for (int now = 1, i = LKa; ~i; --i) {
        tp = (w[u] >> i) & 1;
        if (!son[now][tp]) {
            son[now][tp] = ++cnt;
            tfa[cnt] = now;
        }
        now = son[now][tp];
    }
    for (int now = 1, i = LKa; ~i; --i) {
        tp = (w[u] >> i) & 1 ^ 1;
        if (son[now][tp]) {
            tans[u] += 1 << i;
            now = son[now][tp];
        } else {
            now = son[now][!tp];
        }
    }
    for (auto &&v: to[u]) {
        dfs(v);
    }
    tp2 = 1;
    for (int i = LKa; ~i; --i) {
        tp2 = son[tp2][tp = (w[u] >> i) & 1];
    }
    for (int i = 0; i <= LKa; ++i) {
        tp = son[tp2][0] || son[tp2][1];
        tp2 = tfa[tp2];
        if (!tp) {
            son[tp2][(w[u] >> i) & 1] = 0;
        }
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> q;
    tag1 = tag2 = tag3 = 1;
    if (n <= 1000 && q <= 1000) {
        tag2 = tag3 = 0;
    } else {
        tag1 = 0;
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> w[i];
    }
    for (int i = 1; i < n; ++i) {
        std::cin >> fa[i + 1];
        if (fa[i + 1] != i) {
            tag3 = 0;
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> opt[i];
        if (opt[i] == 0) {
            std::cin >> op1[i] >> op2[i];
            tag2 = 0;
        } else {
            std::cin >> op1[i];
        }
    }
    tag4 = !(tag1 || tag2 || tag3);
    if (tag1 || tag4) {
        for (int i = 1; i <= q; ++i) {
            if (opt[i] == 0) {
                w[op1[i]] = op2[i];
            } else {
                ans = 0;
                for (int j = op1[i]; j; j = fa[j]) {
                    ans = std::max(ans, w[op1[i]] ^ w[j]);
                }
                std::cout << ans << std::endl;
            }
        }
    } else if (tag2) {
        int s[Np], data[Np];
        for (int i = 2; i <= n; ++i) {
            to[fa[i]].push_back(i);
        }
        ++cnt;
        dfs(1);
        for (int i = 1; i <= q; ++i) {
            std::cout << tans[op1[i]] << std::endl;
        }
    } else if (tag3) {
        okline();
    }
    return 0;
}