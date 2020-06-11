#include <bits/stdc++.h>
const int N = 300005;
class node {
   public:
    int k, t;
};
int T, n, q, t, o, x, l, r, z;
int s[N], sum[N];
node d;
std::priority_queue<int, std::vector<int>, std::greater<int> > like;
std::priority_queue<int, std::vector<int>, std::greater<int> > noi[N];
std::priority_queue<node> no;
inline int operator<(node a, node b) { return a.t > b.t; }
inline void add(int u, int l, int r, int x, int y) {
    sum[u] += y;
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) {
        add(u << 1, l, mid, x, y);
    } else {
        add(u << 1 | 1, mid + 1, r, x, y);
    }
}
inline int get(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[u];
    int mid = l + r >> 1, ans = 0;
    if (x <= mid) ans += get(u << 1, l, mid, x, y);
    if (y > mid) ans += get(u << 1 | 1, mid + 1, r, x, y);
    return ans;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n; ++i) std::cin >> s[i];
        std::cin >> q;
        for (int i = 1; i <= q; ++i) {
            std::cin >> t >> o;
            while (!no.empty()) {
                d = no.top();
                if (d.t > t) break;
                no.pop();
                noi[d.k].pop();
                like.push(d.k);
                add(1, 1, n, d.k, 1);
            }
            if (o == 0) {
                std::cin >> x;
                d.k = x;
                d.t = t + s[x];
                no.push(d);
                noi[x].push(d.t);
            } else if (o == 1) {
                z = 0;
                do {
                    if (like.empty()) {
                        std::cout << "Yazid is angry.\n";
                        z = 1;
                        break;
                    }
                    x = like.top();
                    like.pop();
                } while (!get(1, 1, n, x, x));
                if (z) continue;
                add(1, 1, n, x, -1);
                std::cout << x << '\n';
            } else if (o == 2) {
                std::cin >> x;
                if (get(1, 1, n, x, x)) {
                    std::cout << "Succeeded!\n";
                    add(1, 1, n, x, -1);
                } else if (noi[x].empty()) {
                    std::cout << "YJQQQAQ is angry.\n";
                } else {
                    std::cout << noi[x].top() - t << '\n';
                }
            } else {
                std::cin >> l >> r;
                std::cout << get(1, 1, n, l, r) << '\n';
            }
        }
        memset(sum, 0, sizeof(sum));
        while (!like.empty()) like.pop();
        while (!no.empty()) no.pop();
        for (int i = 1; i <= n; ++i) while (!noi[i].empty()) noi[i].pop();
    }
    return 0;
}
