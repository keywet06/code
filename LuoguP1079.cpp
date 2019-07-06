#include <bits/stdc++.h>
std::string a, b;
int main() {
    std::cin >> a;
    std::cin >> b;
    for (int i = 0; i < a.length(); ++i) {
        if (a[i] > 'Z') {
            a[i] -= 'a';
        } else {
            a[i] -= 'A';
        }
    }
    for (int i = 0; i < b.length(); ++i) {
        if (b[i] > 'Z') {
            b[i] = (b[i] - 'a' + 52 - a[i % a.length()]) % 26 + 'a';
        } else {
            b[i] = (b[i] - 'A' + 52 - a[i % a.length()]) % 26 + 'A';
        }
    }
    std::cout << b;
    return 0;
}