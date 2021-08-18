#include <bits/stdc++.h>

const int B = 2;
const int C = 256;

int x, y, rot;
char w[C][B];

inline void init() {
    w['Q'][0] = 'Q';
    w['W'][0] = 'W';
    w['E'][0] = 'E';
    w['A'][0] = 'A';
    w['D'][0] = 'D';
    w['Z'][0] = 'Z';
    w['X'][0] = 'X';
    w['C'][0] = 'C';
    w['Q'][1] = 'C';
    w['W'][1] = 'D';
    w['E'][1] = 'E';
    w['A'][1] = 'X';
    w['D'][1] = 'W';
    w['Z'][1] = 'Z';
    w['X'][1] = 'A';
    w['C'][1] = 'Q';
}

inline void out(std::string s) {
    for (int i = 0; i < s.length(); ++i) std::cout << w[s[i]][rot];
}

void out0(int x, int y);
void out1(int x, int y);

inline void out0(int x, int y) {
    if (y == 4) {
        for (int i = 4; i <= x; ++i) out("WC");
        out("DWAEWA");
        for (int i = 4; i <= x; ++i) out("XQ");
        out("AXCAX");
        return;
    }
    if (y == 5) {
        if (x & 1) {
            
        }
    }
    if (y == 6) {
        for (int i = 4; i <= x; ++i) out("WC");
        out("DWAEAEAEWA");
        for (int i = 3; i <= x >> 1; ++i) out("XZXAWEWA");
        out("XQAXDZDZDZX");
        return;
    }
    out("WE");
    out1(x - 4, y - 4);
    out("ZXD");
    for (int i = 6; i <= x; ++i) out("WC");
    out("DW");
    for (int i = 4; i <= y; ++i) out("AE");
    out("WA");
    for (int i = 4; i <= x; ++i) out("XQ");
    out("AX");
    for (int i = 4; i <= y; ++i) out("DZ");
    out("X");
}

inline void out1(int x, int y) {
    if (y == 4) {
        out("WEAWD");
        for (int i = 4; i <= x; ++i) out("CW");
        out("DXZDXA");
        for (int i = 4; i <= x; ++i) out("QX");
        return;
    }
    if (y == 6) {
        out("WEAEAEAWDCW");
        for (int i = 3; i <= x >> 1; ++i) out("DXZXDWEW");
        out("DXZDZDZDXA");
        for (int i = 4; i <= x; ++i) out("QX");
        return;
    }
    out("W");
    for (int i = 4; i <= y; ++i) out("EA");
    out("WD");
    for (int i = 4; i <= x; ++i) out("CW");
    out("DX");
    for (int i = 4; i <= y; ++i) out("ZD");
    out("XA");
    for (int i = 6; i <= x; ++i) out("QX");
    out("AWE");
    out0(x - 4, y - 4);
    out("ZX");
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> y >> x;
    if (x == 2 && y == 2) {
        std::cout << "WDXA" << std::endl;
    } else if (x == 6 && y == 6) {
        std::cout << "DWCWCWCDWAEAEAEWAXZXAWEWAXQAXDZDZDZX" << std::endl;
    } else if (x == 4 && y >= 4) {
        std::cout << "DEXDW";
        for (int i = 4; i <= y; ++i) std::cout << "QD";
        std::cout << "WAZWAX";
        for (int i = 4; i <= y; ++i) std::cout << "CA";
        std::cout << "X" << std::endl;
    } else if (y == 4 && x >= 4) {
        std::cout << "D";
        for (int i = 4; i <= x; ++i) std::cout << "EX";
        std::cout << "DWQDWA";
        for (int i = 4; i <= x; ++i) std::cout << "ZW";
        std::cout << "AXCAX" << std::endl;
    } else if (x & 1 || y & 1) {
        std::cout << -1 << std::endl;
    } else if (x <= 6 && y <= 6) {
        std::cout << -1 << std::endl;
    } else {
        if (x < y) rot = 1, std::swap(x, y);
        init(), out("D"), out0(x, y);
        std::cout << std::endl;
    }
    return 0;
}