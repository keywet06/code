#include <bits/stdc++.h>
using uint32 = unsigned int;
using uint64 = unsigned long long;
using uint128 = __uint128_t;
using int64 = long long;
long long n;
double k, k2;
__int128_t l, r, m1, m2;
struct ST {
    int que[100005][2];
    int tail;
    void pop() { tail--; }
    void push(int x, int y) {
        tail++;
        que[tail][0] = x;
        que[tail][1] = y;
    }
    void top(int &x, int &y) {
        x = que[tail][0];
        y = que[tail][1];
    }
} st;
inline int outside(uint64 x, uint64 y) {
    return (uint128)y * n > (uint128)x * x;
}
inline int cut_off(uint64 x, uint32 dx, uint32 dy) {
    return (uint128)n * dy <= 2 * (uint128)x * dx;
}
int main() {
    std::cin >> n;
    uint128 ret = 0;
    int dx = 0, dy = 0, ux = 0, uy = 0, mx = 0, my = 0;
    int cnt = 0;
    uint64 x = 0, y = 1;
    st.push(0, 1);
    st.push(1, 0);
    uint64 w = n / 2;
    while (st.tail) {
        st.top(dx, dy);
        while (outside(x + dx, y + dy) && x + dx <= w) {
            ret += y * dx + ((int64)dy - 1) * (dx + 1) / 2;
            x += dx;
            y += dy;
            cnt++;
        }
        if (x + dx > w) break;
        if (x >= n) break;
        while (1) {
            st.pop();
            ux = dx;
            uy = dy;
            st.top(dx, dy);
            if (outside(x + dx, y + dy)) break;
        }
        while (1) {
            mx = ux + dx;
            my = uy + dy;
            if (!outside(x + mx, y + my)) {
                if (cut_off(x + mx, dx, dy)) break;
                ux = mx;
                uy = my;
            } else
                st.push(dx = mx, dy = my);
        }
    }
    for (uint64 i = x + 1; i <= w; ++i) ret = ret + (uint128)i * i / n;
    uint128 z = (uint128)(w) * (w + 1) * (2 * w + 1) / 6 - ret * n;
    std::string str;
    while (z) {
        str = char(z % 10 + '0') + str;
        z /= 10;
    }
    std::cout << str << "\n";
    return 0;
}