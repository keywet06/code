#include <bits/stdc++.h>

using float64 = double;
using float96 = long double;

const int B = 3;
const int N = 1005;
const float96 opt = 1e-9;

int n, q, id;

float96 x, y, z, u, v, w, px, py, pz, ca, cb, cc, min;
float96 tr[N][B][B];

inline float96 exc(float96 x, float96 y) {
    return x / (std::abs(y) < opt ? opt : y);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q;
    std::cout << std::fixed << std::setprecision(10);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < B; ++j) {
            for (int k = 0; k < B; ++k) std::cin >> tr[i][j][k];
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> px >> py;
        id = -1, min = 1e20;
        for (int j = 1; j <= n; ++j) {
            cb = exc(
                exc(px - tr[j][2][0], tr[j][0][0] - tr[j][2][0]) -
                    exc(py - tr[j][2][1], tr[j][0][1] - tr[j][2][1]),
                exc(tr[j][1][0] - tr[j][2][0], tr[j][0][0] - tr[j][2][0]) -
                    exc(tr[j][1][1] - tr[j][2][1], tr[j][0][1] - tr[j][2][1]));
            ca = exc(px - tr[j][2][0] - cb * (tr[j][1][0] - tr[j][2][0]),
                     tr[j][0][0] - tr[j][2][0]);
            cc = 1 - ca - cb;
            x = ca * tr[j][0][0] + cb * tr[j][1][0] + cc * tr[j][2][0];
            y = ca * tr[j][0][1] + cb * tr[j][1][1] + cc * tr[j][2][1];
            z = ca * tr[j][0][2] + cb * tr[j][1][2] + cc * tr[j][2][2];
            if (ca < -opt || cb < -opt || cc < -opt) continue;
            if (z < min) min = z, id = j;
        }
        std::cout << id << ' ' << (~id ? min : 0.0) << '\n';
    }
    return 0;
}