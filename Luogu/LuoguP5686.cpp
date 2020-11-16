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

const int N = 500005;
const int P = 1000000007;

int n;
int64 ans;
int64 a[N], b[N], c[N], d[N];

int main() {
    oct::sync();
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];
    for (int i = n; i; --i) c[i] = (c[i + 1] + b[i] * (n - i + 1)) % P;
    for (int i = 1; i <= n; ++i) d[i] = (d[i - 1] + b[i] * i) % P;
    for (int i = 1; i <= n; ++i) ans += a[i] * c[i] % P * i % P;
    for (int i = 1; i <= n; ++i) ans += d[i - 1] * a[i] % P * (n - i + 1) % P;
    std::cout << ans % P << std::endl;
    return 0;
}