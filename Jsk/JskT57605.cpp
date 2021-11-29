#include <bits/stdc++.h>

template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x < y ? x : (x = y);
}

using dou = double;

const int N = 205;

int n, t;

struct mat {
    dou a[N][N];
    inline mat() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) a[i][j] = 0;
        }
    }
    inline dou *operator[](size_t x) { return a[x]; }
};

inline mat operator*(mat x, mat y) {
    mat ret;
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= n; ++k) {
            for (int j = 1; j <= n; ++j) ret[i][j] += x[i][k] * y[k][j];
        }
    }
    return ret;
}

int sum[N];
int dis[N][N];

mat a, b;

inline mat power(mat x, int y) {
    mat ret = (--y, x);
    while (y) {
        if (y & 1) ret = ret * x;
        x = x * x, y >>= 1;
    }
    return ret;
}

int main() {
    freopen("smart_ball.in", "r", stdin);
    freopen("smart_ball.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> t;
    for (int i = 1; i <= n; ++i) std::cin >> b[i][1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) std::cin >> dis[i][j];
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) mid(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) sum[i] += dis[i][j];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) a[i][j] = dou(dis[i][j]) / sum[j];
    }
    b = power(a, t) * b;
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 1; i <= n; ++i) std::cout << b[i][1] << std::endl;
    return 0;
}