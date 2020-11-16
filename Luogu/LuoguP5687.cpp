// oct object csp-pre-document
#ifndef OCT_OBJECT_CSPx2dPREx2dDOCUMENT
#define OCT_OBJECT_CSPx2dPREx2dDOCUMENT

#include <bits/stdc++.h>

typedef long long int64;

namespace oct {

void sync();

inline void sync() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

#endif  // oct end csp-pre-document

const int N = 300005;

void praw(int64 d);
void pcol(int64 d);

int n, m, r, c;
int64 ans;
int64 a[N], b[N];

inline void praw(int64 d) { ans += d * (m - c), ++r; }
inline void pcol(int64 d) { ans += d * (n - r), ++c; }

int main() {
    oct::sync();
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    std::sort(a, a + n), std::sort(b, b + m);
    ans = a[0] * (m - 1) + b[0] * (n - 1), r = c = 1;
    while (r < n && c < m) a[r] < b[c] ? praw(a[r]) : pcol(b[c]);
    while (r < n) praw(a[r]);
    while (c < n) pcol(b[c]);
    std::cout << ans << std::endl;
    return 0;
}