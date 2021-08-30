#include <bits/stdc++.h>

using int64 = long long;

int up, down, left, right, forw, backw, t;

int64 a, b, ans;

void turnForw() {
    ans += t = down, down = forw, forw = up, up = backw, backw = t;
}

void turnRight() {
    ans += t = down, down = right, right = up, up = left, left = t;
}

void turnForw(int64 turn) {
    
}

void turnRight(int64 turn) {
    
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> a >> b;
    std::cin >> backw >> up >> right >> left >> down >> forw;

    return 0;
}