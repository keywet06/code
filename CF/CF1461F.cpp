#include <bits/stdc++.h>

const int N = 100005;
const int I = N << 3;

int n, fplus, ftime, fredu, x, y, z, l, f, c;
int a[N], pl[N], pr[N], pk[N], pf[N];

std::string s, ans;

inline void solve(int l, int r) {
    while (a[l] == 1 && l < r) s += "1+", ++l;
    if (a[l] == 1) return void(s += "1+");
    while (a[r] == 1 && l < r) ++x, --r;
    x = 1;
    for (int i = l; i <= r; ++i) {
        x *= a[i];
        if (x > I) {
            for (int i = l; i < r; ++i) std::cout << a[i] << '*';
            std::cout << a[r] << '+';
            while (x--) std::cout << "1+";
            return;
        }
    }
    c = 0, x = 1, pl[1] = l;
    for (int i = l; i <= r; ++i) {
        if (a[i] > 1 && a[i + 1] == 1)  {
            pk[i] = x, x = 0;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::cin >> s;
    for (char c : s) ftime |= c == '*', fplus |= c == '+', fredu |= c == '-';
    if (!ftime) {
        for (int i = 1; i < n; ++i) std::cout << a[i] << (fplus ? '+' : '-');
        return std::cout << a[n] << std::endl, 0;
    } else if (!fplus && !fredu) {
        for (int i = 1; i < n; ++i) std::cout << a[i] << '*';
        return std::cout << a[n] << std::endl, 0;
    } else if (!fplus) {
        for (x = 1; x < n, a[x], a[x + 1]; ++x) std::cout << a[x] << '*';
        if (x > 1 && x < n) std::cout << a[x] << '-';
        while (++x < n) std::cout << a[x] << '*';
        return std::cout << a[n] << std::endl, 0;
    }
    ans = "0+", l = 1;
    for (int i = 1; i <= n + 1; ++i) {
        if (a[i]) continue;
        if (a[i - 1]) solve(l, i - 1);
        std::cout << "0+", l = i + 1;
    }
    std::cout << ans.substr(2, (n << 1) - 1) << std::endl;
    return 0;
}