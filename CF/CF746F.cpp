#include <bits/stdc++.h>
using int64 = long long;
#define Fi first
#define Se second
#define Mkp std::make_pair
const int N = 200005;
int happy[N], arr[N];
int64 n, w, k;
int main() {
    while (std::cin >> n >> w >> k) {
        int64 result = 0, ans = 0;
        std::set<std::pair<int, int> > S_, S;
        for (int i = 1; i <= n; ++i) std::cin >> happy[i];
        for (int i = 1; i <= n; ++i) std::cin >> arr[i];
        int l, r;
        l = r = 1;
        while (r <= n) {
            while (r <= n) {
                if (w) {
                    if (k >= (arr[r] + 1) / 2) {
                        k -= (arr[r] + 1) / 2;
                        ans = std::max(ans, result += happy[r]);
                        S_.insert(Mkp(arr[r], r));
                        r++;
                        w--;
                    } else {
                        break;
                    }
                } else {
                    int tmp = S_.begin()->Fi;
                    if (tmp <= arr[r] &&
                        k >= (arr[r] + 1) / 2 - (tmp + 1) / 2 + tmp) {
                        k -= (arr[r] + 1) / 2 - (tmp + 1) / 2 + tmp;
                        ans = std::max(ans, result += happy[r]);
                        auto p = S_.begin();
                        S.insert(*p);
                        S_.erase(p);
                        S_.insert(Mkp(arr[r], r));
                        r++;
                    } else if (tmp > arr[r] && k >= arr[r]) {
                        k -= arr[r];
                        ans = std::max(ans, result += happy[r]);
                        S.insert(Mkp(arr[r], r));
                        r++;
                    } else {
                        break;
                    }
                }
            }
            if (l < r) {
                if (S.find(Mkp(arr[l], l)) != S.end()) {
                    k += arr[l];
                    result -= happy[l];
                    S.erase(Mkp(arr[l], l));
                } else {
                    k += (arr[l] + 1) / 2;
                    result -= happy[l];
                    S_.erase(Mkp(arr[l], l));
                    w++;
                    if (!S.empty()) {
                        auto p = --S.end();
                        k += p->Fi - (p->Fi + 1) / 2;
                        S_.insert(*p);
                        w--;
                        S.erase(p);
                    }
                }
                l++;
            } else {
                l++, r++;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}