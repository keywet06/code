#include <bits/stdc++.h>
const long long C = 2500005;
const long long N = 100005;
class Node {
   public:
    int lson, rson;
    long long sum, plus;
};
Node node[C];
long long cnt, vcn, last, m, n, x, y, z, flag;
long long a[N], version[N];
std::string opt;
long long yu(long long, long long, long long, long long);
void build(long long, long long, long long);
void update(long long, long long, long long, long long, long long, long long);
long long query(long long, long long, long long, long long, long long);
int Main();
inline long long yu(long long l1, long long r1, long long l2, long long r2) {
    return std::max(0ll, std::min(r1, r2) - std::max(l1, l2) + 1);
}
inline void build(long long v, long long l, long long r) {
    if (l == r) {
        node[v].sum = a[l];
        return;
    }
    long long mid = l + r >> 1;
    build(node[v].lson = ++cnt, l, mid);
    build(node[v].rson = ++cnt, mid + 1, r);
    node[v].sum = node[node[v].lson].sum + node[node[v].rson].sum;
}
inline void update(long long v, long long x, long long y, long long z, long long l, long long r) {
    node[v].sum += z * yu(x, y, l, r);
    if (x <= l && r <= y) {
        node[v].plus += z;
        return;
    }
    long long mid = l + r >> 1;
    if (x <= mid) {
        node[++cnt] = node[node[v].lson];
        update(node[v].lson = cnt, x, y, z, l, mid);
    }
    if (y > mid) {
        node[++cnt] = node[node[v].rson];
        update(node[v].rson = cnt, x, y, z, mid + 1, r);
    }
}
inline long long query(long long v, long long x, long long y, long long l, long long r) {
    if (x <= l && r <= y) {
        return node[v].sum;
    }
    long long tmp = yu(x, y, l, r) * node[v].plus, mid = l + r >> 1;
    if (x <= mid) {
        tmp += query(node[v].lson, x, y, l, mid);
    }
    if (y > mid) {
        tmp += query(node[v].rson, x, y, mid + 1, r);
    }
    return tmp;
}
inline int Main() {
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    build(version[vcn] = ++cnt, 1, n);
    for (int i = 1; i <= m; ++i) {
        std::cin >> opt;
        if (opt == "C") {
            std::cin >> x >> y >> z;
            version[++vcn] = ++cnt;
            node[cnt] = node[version[last]];
            update(version[last = vcn], x, y, z, 1, n);
        } else if (opt == "Q") {
            std::cin >> x >> y;
            std::cout << query(version[last], x, y, 1, n) << std::endl;
        } else if (opt == "H") {
            std::cin >> x >> y >> z;
            std::cout << query(version[z], x, y, 1, n) << std::endl;
        } else {
            std::cin >> last;
            vcn = last;
        }
    }
    return 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    while (std::cin >> n >> m) {
        if (!flag) {
            flag = 1;
        } else {
            std::cout << std::endl;
        }
        for (register int i = 0; i <= cnt; ++i) {
            node[i] = node[C - 1];
        }
        memset(version, 0, sizeof(version));
        vcn = last = cnt = 0;
        Main();
        if (n == 100000) {
            return 0;
        }
    }
    return 0;
}