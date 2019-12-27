#include <bits/stdc++.h>
const int C = 20000005;
const int N = 500005;
class Node {
   public:
    int size;
    int son[2];
};
class Pqtp {
   public:
    int r, k;
    long long ans;
    Pqtp(int, int, long long);
};
int cnt, n, k;
int tree[N];
long long ans;
long long a[N], b[N];
Node nd[C];
std::priority_queue<Pqtp> pq;
int operator<(Pqtp, Pqtp);
void update(long long);
long long get(int, long long);
inline Pqtp::Pqtp(int x, int y, long long z) {
    this->r = x;
    this->k = y;
    this->ans = z;
}
inline int operator<(Pqtp x, Pqtp y) {
    return x.ans < y.ans;
}
inline void update(long long x) {
    static long long v, t;
    v = 1;
    for (int i = 33; ~i; --i) {
        ++nd[v].size;
        t = (x >> i) & 1;
        if (!nd[v].son[t]) {
            nd[v].son[t] = ++cnt;
        }
        v = nd[v].son[t];
    }
    ++nd[v].size;
}
inline long long get(int k, long long x) {
    static long long v, t, ans;
    v = 1;
    ans = 0;
    --k;
    for (int i = 33; ~i; --i) {
        t = (x >> i) & 1;
        if (k >= nd[nd[v].son[t ^ 1]].size) {
            k -= nd[nd[v].son[t ^ 1]].size;
            v = nd[v].son[t];
        } else {
            ans |= 1ll << i;
            v = nd[v].son[t ^ 1];
        }
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    k *= 2;
    cnt = 1;
    update(0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        b[i] = a[i] ^ b[i - 1];
        update(b[i]);
    }
    for (int i = 0; i <= n; ++i) {
        pq.push((Pqtp){i, 1, get(1, b[i])});
    }
    for (int i = 1; i <= k; ++i) {
        Pqtp v = pq.top();
        pq.pop();
        pq.push((Pqtp){v.r, v.k + 1, get(v.k + 1, b[v.r])});
        ans += v.ans;
    }
    std::cout << (ans / 2) << std::endl;
    return 0;
}