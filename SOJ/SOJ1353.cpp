#include <bits/stdc++.h>

#define mkp std::make_pair
#define fir first
#define sec second

using pair = std::pair<int, int>;

const int N = 200005;

int n, x, y, c;
int d[N];

std::string s, t;

std::vector<pair> a, b;

inline void add(int x, int l, std::vector<pair> &v) {
    v.push_back(mkp(x, x + l - 1));
}

inline void move(int l, int a, int b, std::vector<pair> &v) {
    if (!a || !b) return;
    if (a == b) return add(l, a + b, v);
    if (a < b) return add(l, a + a, v), move(l + a + a, a, b - a - a, v);
    if (a > b) return add(l + a - b, b + b, v), move(l, a - b, b, v);
}

inline void split(int l, int r, std::vector<pair> &v) {
    if (l == r) return;
    int mid = l + r >> 1;
    split(l, mid, v), split(mid + 1, r, v);
    move(d[mid] - mid + l, mid - l + 1, d[r] - d[mid] - r + mid, v);
}

inline std::vector<pair> solve(std::string s) {
    std::vector<pair> v;

    s = ' ' + s, c = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '1') d[++c] = i;
    }
    split(1, c, v), move(d[c] - c + 1, c, n - d[c], v);
    return v;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    std::cin >> s;
    std::cin >> t;
    for (int i = 0; i < n; ++i) x += s[i] == '0';
    for (int i = 0; i < n; ++i) y += t[i] == '0';
    if (x != y) return std::cout << -1 << '\n', 0;
    a = solve(s);
    b = solve(t);
    while (!b.empty()) a.push_back(b[b.size() - 1]), b.pop_back();
    std::cout << (n = a.size()) << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << a[i].fir - 1 << ' ' << a[i].sec - 1 << '\n';
    }
    return 0;
}