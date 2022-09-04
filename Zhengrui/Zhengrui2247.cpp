#include <bits/stdc++.h>

typedef long long int64;

const int N = 100000;

char Str[N + 2];

int a[N + 1];
int b[27];

std::unordered_map<int, int> Map;

std::vector<std::pair<int, int64> > p[N + 1];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("\n%s", Str + 1);
    for (int i = 1; i <= 26; ++i) scanf("%d", b + i);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        int Hash = 0;
        for (int j = i; j <= n; ++j) ++Map[Hash = (Hash * 2333ll + Str[j] * 2) % 998244353];
    }
    for (int i = 1; i <= n; ++i) {
        int64 Sb = 0;
        int Hash = 0;
        for (int j = i, occ = -1; j <= n; ++j) {
            Sb += b[Str[j] ^ 96];
            const int t = Map[Hash = (Hash * 2333ll + Str[j] * 2) % 998244353];
            if (t != occ) {
                occ = t;
                const int64 prd = a[occ] * Sb;
                if (p[i].empty() || prd < p[i].back().second) p[i].emplace_back(j, prd);
            }
        }
    }
    for (int i = 1, l, r; i <= q; ++i) {
        scanf("%d %d", &l, &r);
        int64 Ans = p[l][0].second;
        for (int j = l; j <= r; ++j) {
            const int64 Now = std::prev(std::upper_bound(p[j].begin(), p[j].end(), std::make_pair(r + 1, 0ll)))->second;
            if (Now < Ans) Ans = Now;
        }
        printf("%lld\n", Ans);
    }
    return 0;
}