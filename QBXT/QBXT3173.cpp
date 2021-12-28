#include <bits/stdc++.h>

template <typename Type, typename DType>
inline Type &Mid(Type &x, DType y) {
    return x < y ? x : (x = y);
}

template <typename Type, typename DType>
inline Type &Mad(Type &x, DType y) {
    return x > y ? x : (x = y);
}

const int N = 20005;
const int INF = int(1e9) + 7;

int n, L, l, r, Up, Do, Le, Ri;
int px[N], py[N], pc[N];

inline void GetMax() {
    Up = Le = INF, Do = Ri = -INF;
    for (int i = 1; i <= n; ++i) {
        if (pc[i]) continue;
        Mid(Up, px[i]), Mad(Do, px[i]);
        Mid(Le, py[i]), Mad(Ri, py[i]);
    }
}

inline bool Check3() {
    return GetMax(), Ri - Le <= L && Do - Up <= L;
}

inline void Xor(int u, int d, int l, int r, int c) {
    for (int i = 1; i <= n; ++i) {
        if (px[i] >= u && px[i] <= d && py[i] >= l && py[i] <= r) pc[i] ^= c;
    }
}

inline bool Check2() {
    GetMax();
    int UP = Up, DO = Do, LE = Le, RI = Ri, F;
    Xor(UP, UP + L, LE, LE + L, 2);
    F = Check3();
    Xor(UP, UP + L, LE, LE + L, 2);
    if (F) return true;
    Xor(DO - L, DO, LE, LE + L, 2);
    F = Check3();
    Xor(DO - L, DO, LE, LE + L, 2);
    if (F) return true;
    Xor(UP, UP + L, RI - L, RI, 2);
    F = Check3();
    Xor(UP, UP + L, RI - L, RI, 2);
    if (F) return true;
    Xor(DO - L, DO, RI - L, RI, 2);
    F = Check3();
    Xor(DO - L, DO, RI - L, RI, 2);
    if (F) return true;
    return false;
}

inline bool Check1() {
    GetMax();
    int UP = Up, DO = Do, LE = Le, RI = Ri, F;
    Xor(UP, UP + L, LE, LE + L, 1);
    F = Check2();
    Xor(UP, UP + L, LE, LE + L, 1);
    if (F) return true;
    Xor(DO - L, DO, LE, LE + L, 1);
    F = Check2();
    Xor(DO - L, DO, LE, LE + L, 1);
    if (F) return true;
    Xor(UP, UP + L, RI - L, RI, 1);
    F = Check2();
    Xor(UP, UP + L, RI - L, RI, 1);
    if (F) return true;
    Xor(DO - L, DO, RI - L, RI, 1);
    F = Check2();
    Xor(DO - L, DO, RI - L, RI, 1);
    if (F) return true;
    return false;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> px[i] >> py[i];
    l = 0, r = 1e9;
    while (l < r) {
        L = l + r >> 1;
        if (Check1()) {
            r = L;
        } else {
            l = L + 1;
        }
    }
    std::cout << l << std::endl;
    return 0;
}