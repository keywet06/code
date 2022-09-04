#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Debug << std::endl

enum card { A0, A1, A2, A3, A4, B0, B1, B2, B3, B4 };

int a[1 << 18];
int T, a0, a1, a2, a3, a4, b0, b1, b2, b3, b4;

#define a1b4 a0, a1, a2, a3, a4, b0, b1, b2, b3, b4
#define a1b4a int &a0, int &a1, int &a2, int &a3, int &a4, int &b0, int &b1, int &b2, int &b3, int &b4
#define clear a0 = ca0, a1 = ca1, a2 = ca2, a3 = ca3, a4 = ca4, b0 = cb0, b1 = cb1, b2 = cb2, b3 = cb3, b4 = cb4
#define num a0 | a1 << 2 | a2 << 4 | a3 << 5 | a4 << 7 | b0 << 9 | b1 << 11 | b2 << 13 | b3 << 14 | b4 << 16

inline void die(a1b4a, card c) {
    switch (c) {
        case A0:
            return --a0, void(0);
        case A1:
            return --a1, ++a3, void(0);
        case A2:
            return --a2, ++a4, void(0);
        case A3:
            return --a3, ++a0, void(0);
        case A4:
            return --a4, void(0);
        case B0:
            return --b0, void(0);
        case B1:
            return --b1, ++b3, void(0);
        case B2:
            return --b2, ++b4, void(0);
        case B3:
            return --b3, ++b0, void(0);
        case B4:
            return --b4, void(0);
    }
}

inline int Dfs(int x) {
    if (a[x]) return a[x] - 1;
    int a0 = (x >> 0) & 3, a1 = (x >> 2) & 3, a2 = (x >> 4) & 1, a3 = (x >> 5) & 3, a4 = (x >> 7) & 3;
    int b0 = (x >> 9) & 3, b1 = (x >> 11) & 3, b2 = (x >> 13) & 1, b3 = (x >> 14) & 3, b4 = (x >> 16) & 3;
    // Debug << "Dfs((" << a0 << ", " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << "), (" << b0 << ", " << b1 <<
    // ", "
    //   << b2 << ", " << b3 << ", " << b4 << "))" << std::endl;
    if (!(a0 + a1 + a2 + a3 + a4) || !(b0 + b1 + b2 + b3 + b4)) return (a[x] = bool(a0 + a1 + a2 + a3 + a4) + 1) - 1;
    int ca0 = a0, ca1 = a1, ca2 = a2, ca3 = a3, ca4 = a4, cb0 = b0, cb1 = b1, cb2 = b2, cb3 = b3, cb4 = b4;
    int *pa[5] = {&a0, &a1, &a2, &a3, &a4}, *pb[5] = {&b0, &b1, &b2, &b3, &b4};
    card ca[5] = {A0, A1, A2, A3, A4}, cb[5] = {B0, B1, B2, B3, B4};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (!*pa[i] || !*pb[j]) continue;
            // Debug << "Argument " << i << ' ' << j << std::endl;
            // Debug << "Before((" << a0 << ", " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << "), (" << b0 << ", "
            //   << b1 << ", " << b2 << ", " << b3 << ", " << b4 << "))" << std::endl;
            if (i < 3 || j != 0) die(a1b4, ca[i]);
            if (j < 3 || i != 0) die(a1b4, cb[j]);
            // Debug << "After((" << a0 << ", " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << "), (" << b0 << ", "
            //   << b1 << ", " << b2 << ", " << b3 << ", " << b4 << "))" << std::endl;
            if (Dfs(num)) return (a[x] = 2) - 1;
            clear;
        }
    }
    return (a[x] = 1) - 1;
}

inline void die(card c) {
    switch (c) {
        case A0:
            return --a0, void(0);
        case A1:
            return --a1, ++a3, void(0);
        case A2:
            return --a2, ++a4, void(0);
        case A3:
            return --a3, ++a0, void(0);
        case A4:
            return --a4, void(0);
        case B0:
            return --b0, void(0);
        case B1:
            return --b1, ++b3, void(0);
        case B2:
            return --b2, ++b4, void(0);
        case B3:
            return --b3, ++b0, void(0);
        case B4:
            return --b4, void(0);
    }
}

template <typename... Args>
inline void die(card c, Args... args) {
    switch (c) {
        case A0:
            return a0 ? die(A0) : die(args...);
        case A1:
            return a1 ? die(A1) : die(args...);
        case A2:
            return a2 ? die(A2) : die(args...);
        case A3:
            return a3 ? die(A3) : die(args...);
        case A4:
            return a4 ? die(A4) : die(args...);
        case B0:
            return b0 ? die(B0) : die(args...);
        case B1:
            return b1 ? die(B1) : die(args...);
        case B2:
            return b2 ? die(B2) : die(args...);
        case B3:
            return b3 ? die(B3) : die(args...);
        case B4:
            return b4 ? die(B4) : die(args...);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> T;
    while (T--) {
        std::cin >> a1 >> a2 >> a3 >> a4;
        std::cin >> b1 >> b2 >> b3 >> b4;
        a0 = b0 = 0;
        while (a0 + a1 + a2 + a3 + a4 && b0 + b1 + b2 + b3 + b4) {
            if (std::max({a0, a2, a3, a4, b0, b2, b3, b4}) < 2 && std::max(a1, b1) < 2) {
                a0 = Dfs(num), a1 = a2 = a3 = a4 = b0 = b1 = b2 = b3 = b4 = 0;
            } else if (a0 && b0 && a0 + a1 + a3 > b0 + b1 + b3 + b1 + b2) {
                die(A0), die(B0);
            } else if (a0 && b1 + b2) {
                die(A0), die(B1, B2);
            } else if (b0 && a3 + a4) {
                die(B0);
            } else if (a1 + a2 + a3 + a4 && b1 + b2 + b3 + b4) {
                if (a1 + a3 + a0 <= b1 + b2) {
                    die(A3, A1, A4, A2), die(B3, B1, B4, B2);
                } else {
                    die(A3, A1, A4, A2), die(B3, B4, B1, B2);
                }
            } else if (b1 + b2 + b3 + b4) {
                a0 = 0;
            } else {
                die(A0), die(B0);
            }
            Debug << "a & b: " << std::endl;
            Debug << "a: (" << a0 << ", " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ")" << std::endl;
            Debug << "b: (" << b0 << ", " << b1 << ", " << b2 << ", " << b3 << ", " << b4 << ")" << std::endl;
        }
        std::cout << (a0 + a1 + a2 + a3 + a4 ? "Yes" : "No") << std::endl;
    }
    return 0;
}