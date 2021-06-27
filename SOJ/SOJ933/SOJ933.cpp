#include <bits/stdc++.h>

int T, id;

std::string s;

int main() {
    std::cin >> id >> T;
    while (T--) {
        std::cin >> s;
        s = "factor " + s;
        std::cerr << s << std::endl;
        system(s.data());
        std::cin >> s;
    }
    return 0;
}