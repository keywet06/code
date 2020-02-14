#include <bits/stdc++.h>
const int N = 8e4 + 10;
struct node {
    int opt, left, right, x;
};
int n, m, a[N];
node q[N];
namespace Subtask2 {

int cnt[N];
void main() {
    for (int opt, left, right, x, i = 1; i <= m; i++) {
        std::cin >> opt >> left >> right >> x;
        if (opt == 1) {
            while (left != right + 1) {
                a[left] = std::min(a[left], x);
                left++;
            }
        } else {
            std::fill(cnt + 1, cnt + n + 1, 0);
            while (left != right + 1) {
                cnt[a[left++]]++;
            }
            for (int j = 1; j <= n; j++) {
                cnt[j] += cnt[j - 1];
                if (cnt[j] >= x) {
                    std::cout << j << std::endl;
                    break;
                }
            }
        }
    }
}

}  // namespace Subtask2
namespace Subtask {

std::multiset<int> set;
std::vector<int> in[N], out[N];
const int M = 32 * N;
int id, sz[M], ls[M], rs[M], T[N];
void update(int pre, int &u, int left, int right, int p) {
    u = ++id;
    sz[u] = sz[pre] + 1;
    ls[u] = ls[pre];
    rs[u] = rs[pre];
    if (left == right) return;
    int mid = (left + right) >> 1;
    if (p <= mid) {
        update(ls[pre], ls[u], left, mid, p);
    } else {
        update(rs[pre], rs[u], mid + 1, right, p);
    }
}
int query(int L, int R, int left, int right, int k) {
    if (left == right) {
        return left;
    }
    int mid = (left + right) >> 1, lsz = sz[ls[R]] - sz[ls[L]];
    if (lsz >= k) {
        return query(ls[L], ls[R], left, mid, k);
    }
    return query(rs[L], rs[R], mid + 1, right, k - lsz);
}
void main() {
    int right = 0;
    for (int i = 1; i <= m; i++) {
        if (q[i].opt == 1) {
            in[q[i].left].push_back(q[i].x);
            if (q[i].right ^ n) {
                out[q[i].right + 1].push_back(q[i].x);
            }
            right = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int x : in[i]) {
            set.insert(x);
        }
        for (int x : out[i]) {
            set.erase(set.lower_bound(x));
        }
        if (set.size()) {
            a[i] = std::min(a[i], *set.begin());
        }
    }
    for (int i = 1; i <= n; i++) {
        update(T[i - 1], T[i], 1, n, a[i]);
    }
    for (int i = 1; i <= m; i++) {
        if (q[i].opt == 2) {
            int left = q[i].left, right = q[i].right, k = q[i].x;
            std::cout << query(T[left - 1], T[right], 1, n, k) << std::endl;
        }
    }
}

}  // namespace Subtask
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    if (n <= 1000 && m <= 1000) {
        Subtask2::main();
    } else {
        bool tag2 = 0, tag = 1;
        for (int i = 1; i <= m; i++) {
            std::cin >> q[i].opt >> q[i].left >> q[i].right >> q[i].x;
            if (q[i].opt == 1) {
                if (tag2) {
                    tag = 0;
                }
            } else {
                tag2 = 1;
            }
            if (q[i].x > n) {
                q[i].x = n;
            }
        }
        Subtask::main();
    }
    return 0;
}