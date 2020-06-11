#include <bits/stdc++.h>
const int B = 2;
const int K = 100005;
class nd {
   public:
    int x, y;
    long long v;
    nd(long long kval, int kx, int ky) { v = kval, x = kx, y = ky; }
};
int n, k, cnt;
int c[K], v[K], id[K];
long long x, y;
std::vector<long long> a[K], b[K];
std::priority_queue<nd> pq;
inline int cmp(int x, int y) { return b[x][0] > b[y][0]; }
inline int operator<(nd x, nd y) { return x.v < y.v; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> k >> n;
    for (int i = 1; i <= k; ++i) {
        std::cin >> c[++cnt];
        if (c[cnt] == 1) {
            std::cin >> x;
            y += x;
            --cnt;
            continue;
        }
        b[cnt].resize(c[cnt]);
        for (int j = 0; j < c[cnt]; ++j) {
            std::cin >> b[cnt][j];
        }
        std::sort(b[cnt].begin(), b[cnt].end(), std::greater<long long>());
        y += b[cnt][0];
        for (int j = 1; j < c[cnt]; ++j) {
            b[cnt][j - 1] = b[cnt][j] - b[cnt][j - 1];
        }
        b[cnt].pop_back();
        id[cnt] = cnt;
    }
    if (cnt == 0) {
        std::cout << y << std::endl;
        return 0;
    }
    std::sort(id + 1, id + cnt + 1, cmp);
    for (int i = 1; i <= cnt; ++i) c[i] = (a[i] = b[id[i]]).size();
    std::cout << y << " ";
    y += a[1][0];
    pq.push(nd(y, 1, 0));
    for (int i = 1; i < n; ++i) {
        nd t = pq.top();
        pq.pop();
        std::cout << t.v << ' ';
        if (t.y < c[t.x] - 1) pq.push(nd(t.v + a[t.x][t.y + 1], t.x, t.y + 1));
        if (t.x < cnt) {
            pq.push(nd(t.v + a[t.x + 1][0], t.x + 1, 0));
            if (!t.y) pq.push(nd(t.v - a[t.x][0] + a[t.x + 1][0], t.x + 1, 0));
        }
    }
    std::cout << std::endl;
    return 0;
}
