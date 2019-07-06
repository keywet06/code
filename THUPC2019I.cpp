#include "fraction.hpp"
const int N = 500005;
long long n;
long long a[N], b[N];
kw::fraction<long long> sum;
std::priority_queue<long long> p1;
std::priority_queue<long long, std::vector<long long>, std::greater<long long> > p2;
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &b[i]);
    }
    for (int i = 1; i <= n; ++i) {
        sum += kw::fraction<long long>(a[i]);
        
    }
    return 0;
}