#include <bits/stdc++.h>
#include "decimal.h"

int T, p, r, f;

Decimal a, b, c;

std::string s, k, u;

int main(int argv, char** argc) {
    if (argv == 1) return std::cout << "No file!" << std::endl, 0;
    u = s = argc[1];
    std::ifstream iin, oin;
    iin.open(s + ".out");
    oin.open(s + ".in");
    oin >> T >> T;
    for (int e = 1; e <= T; ++e) {
        a = 1;
        while (1) {
            std::getline(iin, s);
            if (s == "") break;
            k = "";
            for (int i = 0; i < s.length(); ++i) {
                if (s[i] == ' ') {
                    b = Decimal(k);
                    k = "";
                    continue;
                }
                k = k + s[i];
            }
            c = Decimal(k);
            r = c.to_int();
            while (r--) a = a * b;
        }
        oin >> b;
        if (a != b) std::cerr << u << '#' << e << " failed." << std::endl, f = 1;
        oin >> b;
    }
    if (!f) std::cerr << u << " checked!" << std::endl;
    return 0;
}