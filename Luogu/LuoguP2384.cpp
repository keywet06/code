#include <bits/stdc++.h>

#define fir first
#define sec second
#define mkp std::make_pair
#define pub push_back
#define pus push
#define pob pop_back

using db = double;
using i5 = int;
using pi5db = std::pair<i5, db>;
using pi5pi5db = std::pair<i5, pi5db>;

namespace oct {

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

} // namespace oct

const int N = 10005;
const int P = 9987;

double w;
double dd[N];

int n, m, x, y, z;
int di[N], used[N];

std::vector<pi5pi5db> to[N];

int main() {
    oct::ios();
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z, w = log(z);
        to[x].pub(mkp(y, mkp(z, w)));
    }
    for (int i = 1; i <= n; ++i) dd[i] = 1e9;
    dd[1] = 0, di[1] = 1;
    for (int i = 1; i <= n; ++i) {
        w = 1e9;
        for (int j = 1; j <= n; ++j) {
            if (!used[j] && dd[j] < w) w = dd[j], x = j;
        }
        used[x] = 1, z = di[x];
        for (pi5pi5db v : to[x]) {
            if (w + v.sec.sec < dd[v.fir]) {
                dd[v.fir] = w + v.sec.sec;
                di[v.fir] = (z * v.sec.fir) % P;
            }
        }
    }
    std::cout << di[n] << std::endl;
    return 0;
}