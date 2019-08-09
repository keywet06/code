#include <bits/stdc++.h>
const long long N = 5e5 + 7;
struct point {
    long long left, right;
    mutable long long height;
};
class chaxun {
   public:
    long long opt, left, right;
    long long v;
};
char opt;
chaxun q[N];
long long n, m;
long long a[N];
long long vl;
long long vals[N];
long long cnts[N];
std::set<point> set;
std::set<point>::iterator split(long long);
std::vector<long long> vector;
long long bitset(long long);
void modf(long long, long long);
long long count(long long);
long long query(long long);
void insert(long long, long long, long long);
void init(long long, long long, long long);
long long check(long long);
long long operator<(point, point);
int main() {
    vector.emplace_back(-1);
    scanf("%lld %lld", &n, &m);
    for (long long i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        vector.emplace_back(a[i]);
    }
    for (long long i = 1; i <= m; ++i) {
        scanf("%c", &opt);
        while (opt != 'Q' && opt != 'M') {
            scanf("%c", &opt);
        }
        if (opt == 'Q') {
            q[i].opt = 1;
            scanf("%lld", &q[i].v);
        } else {
            scanf("%lld %lld %lld", &q[i].left, &q[i].right, &q[i].v);
            vector.emplace_back(q[i].v);
        }
    }
    std::sort(vector.begin(), vector.end());
    vector.erase(unique(vector.begin(), vector.end()), vector.end());
    for (long long i = 1; i <= n; ++i) {
        long long u = std::lower_bound(vector.begin(), vector.end(), a[i]) -
                vector.begin();
        modf(u, 1);
        insert(i, i, u);
    }
    insert(n + 1, n + 1, 0);
    for (long long i = 1; i <= m; ++i) {
        if (q[i].opt) {
            long long left = 1, right = vector.size(), zhk = 1;
            vl = q[i].v;
            while (left <= right) {
                long long mid = (left + right) >> 1;
                if (check(mid)) {
                    left = (zhk = mid) + 1;
                } else {
                    right = mid - 1;
                }
            }
            long long f1 = vl + query(zhk), f2 = count(zhk);
            long long d = std::__gcd(f1, f2);
            printf("%lld/%lld\n", f1 / d, f2 / d);
        } else {
            long long left = q[i].left, right = q[i].right, v = q[i].v;
            v = lower_bound(vector.begin(), vector.end(), v) - vector.begin();
            init(left, right, v);
        }
    }
    return 0;
}
inline long long bitset(long long x) { return x & -x; }
inline void modf(long long i, long long cnt) {
    long long val = vector[i];
    for (; i <= vector.size(); i += i & (-i)) {
        cnts[i] += cnt;
        vals[i] += cnt * 1LL * val;
    }
}
inline long long count(long long i) {
    long long x = 0;
    for (; i; i &= i - 1) {
        x += cnts[i];
    }
    return x;
}
inline long long query(long long i) {
    long long x = 0;
    for (; i; i &= i - 1) {
        x += vals[i];
    }
    return x;
}
inline std::set<point>::iterator split(long long u) {
    std::set<point>::iterator it = set.lower_bound((point){u});
    if (it != set.end() && it->left == u) {
        return it;
    }
    --it;
    long long left = it->left, right = it->right, v = it->height;
    set.erase(it);
    set.insert((point){left, u - 1, v});
    return set.insert((point){u, right, v}).first;
}
inline void insert(long long left, long long right, long long height) {
    set.insert((point){left, right, height});
}
inline void init(long long left, long long right, long long val) {
    std::set<point>::iterator R = split(right + 1), L = split(left);
    for (std::set<point>::iterator i = L; i != R; ++i) {
        modf(i->height, -(i->right - i->left + 1));
    }
    set.erase(L, R);
    set.insert((point){left, right, val});
    modf(val, right - left + 1);
}
inline long long check(long long height) {
    long long cnts = count(height), v = query(height);
    return vl + v >= vector[height] * cnts;
}
inline long long operator<(point a, point b) { return a.left < b.left; }
