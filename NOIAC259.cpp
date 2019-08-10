#include <bits/stdc++.h>
std::queue<long long> queue;
std::map<long long, int> map;
int main() {
    scanf("%d %d %d %d", xa, ya, xb, yb);
    xa += 5000000;
    xb += 5000000;
    ya += 5000000;
    yb += 5000000;
    la = ya - yb;
    lb = xb - xa;
    lc = xa * yb - xb * ya;
    
    return 0;
}