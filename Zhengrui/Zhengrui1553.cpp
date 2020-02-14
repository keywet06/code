#include <bits/stdc++.h>
#ifndef LOCAL
#define eprintf(...) fprintf(stderr, _VA_ARGS)
#else
#define eprintf(...) 42
#endif

const int N = 3e5 + 10;

int n, q, T, tail, x, y, ans;
int r[N];
std::pair<int, int> que[N];
std::map<std::pair<int, int>, std::pair<int, int> > map;
const int ds[2][8] = {
    {-1, 0, 1, 1, 1, 0, -1, -1},
    {-1, -1, -1, 0, 1, 1, 1, 0},
};

template <typename _Tp>
inline _Tp &chkmin(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}
template <typename _Tp>
inline _Tp &chkmax(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}
inline std::pair<int, int> find(std::pair<int, int> x) {
    if (!map.count(x) || map[x] == x) {
        return map[x] = x;
    } else {
        return map[x] = find(map[x]);
    }
}
inline bool check(std::pair<int, int> a, std::pair<int, int> b) {
    return abs(a.first - b.first) <= 1 && abs(a.second - b.second) <= 1;
}
inline bool chk(int x, int y) {
    return map.count(std::make_pair(x - 1, y)) &&
           map.count(std::make_pair(x + 1, y)) &&
           map.count(std::make_pair(x, y - 1)) &&
           map.count(std::make_pair(x, y + 1));
}
inline void work(int x) {
    for (int i = 1; i <= tail; ++i)
        if (!r[i] && check(que[x], que[i])) r[i] = 1, work(i);
    return;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> q >> T;
    ans = 1;
    for (int i = 1; i <= q; ++i) {
        std::cin >> x >> y;
        if (i != 1) {
            x ^= (ans * T);
            y ^= (ans * T);
        }
        tail = 0;
        std::pair<int, int> last = std::make_pair(1e9 + 10, 1e9 + 10);
        for (int i = 0; i < 8; ++i) {
            int tx = x + ds[0][i], ty = y + ds[1][i];
            std::pair<int, int> gx = std::make_pair(tx, ty);
            if (map.count(gx)) {
                que[++tail] = gx;
            }
        }
        std::pair<int, int> gx = find(std::make_pair(x, y));
        if (chk(x, y)) {
            std::cout << --ans << std::endl;
            for (int i = 1; i <= tail; ++i) {
                map[que[i]] = gx;
            }
            continue;
        }
        for (int i = 1; i <= tail; ++i) {
            r[i] = 0;
        }
        int tt = 0;
        for (int i = 1; i <= tail; ++i) {
            if (!r[i]) {
                r[i] = 2;
                work(i);
            }
        }
        for (int i = 1; i <= tail; ++i) {
            if (r[i] == 2) {
                que[++tt] = que[i];
            }
        }
        tail = tt;
        for (int i = 1; i <= tail; ++i) {
            que[i] = find(que[i]);
        }
        sort(que + 1, que + tail + 1);
        last = std::make_pair(1e9 + 10, 1e9 + 10);
        int now = 0;
        for (int i = 1; i <= tail; ++i) {
            if (que[i] != last) {
                ans += std::max(0, now - 1);
                last = que[i];
                now = 1;
            } else {
                ++now;
            }
        }
        ans += std::max(0, now - 1);
        for (int i = 1; i <= tail; ++i) {
            map[que[i]] = gx;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
