#include <bits/stdc++.h>
#include "KMP.hpp"
std::string s1, s2;
std::vector<int> v;
int len;
int a[1000005];
int main() {
    std::cin >> s2;
    std::cin >> s1;
    KMPinit(s1, a);
    v = KMPs(s1, s2, a);
    len = v.size();
    for (int i = 0; i < len; ++i) printf("%d\n", v[i] + 1);
    for (int i = 0; i < s1.length(); ++i) printf("%d ", a[i] + 1);
    return 0;
}
