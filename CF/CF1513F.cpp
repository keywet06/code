#include <bits/stdc++.h>

#define fir first
#define sec second
#define mkp std::make_pair

using int64 = long long;
using dpair = std::pair<std::pair<int, int>, int>;

const int B = 2;
const int N = 200005;

int n, k, x, pan;
int d[B];
int a[N], b[N];

int64 ans;

dpair q[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];
    for (int i = 1; i <= n; ++i) {
        if (a[i] < b[i]) {
            ++k, ans += (q[k].fir.sec = b[i]) - (q[k].fir.fir = a[i]);
        } else if (a[i] > b[i]) {
            ++k, ans += (q[k].fir.sec = a[i]) - (q[k].fir.fir = b[i]);
            q[k].sec = 1;
        }
    }
    std::sort(q + 1, q + k + 1);
    memset(d, 63, sizeof(d));
    for (int i = k; i; --i) {
        if (d[!q[i].sec] < q[i].fir.sec) {
            pan = std::max(pan,
                           q[i].fir.sec - std::max(d[!q[i].sec], q[i].fir.fir));
        }
        d[q[i].sec] = std::min(d[q[i].sec], q[i].fir.fir);
    }
    ans -= pan << 1;
    std::cout << ans << std::endl;
    return 0;
}