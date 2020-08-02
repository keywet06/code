#include <bits/stdc++.h>
const int N = 300005;
const long long mod = 1050000011;
const long long D = 1050000031;
int power(int a, int p) {
    int as = 1;
    while (p) {
        if (p & 1) as = 1ll * as * a % mod;
        a = 1ll * a * a % mod;
        p >>= 1;
    }
    return as;
}
int pows(int a, int p, int mod) {
    int as = 1;
    while (p) {
        if (p & 1) as = 1ll * as * a % mod;
        a = 1ll * a * a % mod;
        p >>= 1;
    }
    return as;
}
int n, as, ct3;
int ty[6] = {0, D};
int aa[N], ab[N], v[N], a2[N], a3[N], a4[N], a5[N], a6[N];
int a1[6][N];
bool check(int l, int r, int fy, int tmpu) {
    for (int i = 1; i <= 1; i++) {
        if ((a1[i][r] - a1[i][l - 1] + ty[i]) % ty[i] != tmpu) return 0;
    }
    return 1;
}
struct sth {
    int a, b;
    friend bool operator<(sth a, sth b) {
        return a.a == b.a ? a.b < b.b : a.a < b.a;
    }
} fy[N];
long long as1[10005000], ct1;
struct hashs {
    int hd[N * 6], nt[N * 6], v[N * 6], s[N * 6], ct;
    std::queue<int> st1;
    hashs() { ct = 0; }
    void add(int x, int y) {
        s[++ct] = y;
        v[ct] = x;
        nt[ct] = hd[x & 1048575];
        hd[x & 1048575] = ct;
        st1.push(x & 1048575);
    }
    void init() {
        ct = 0;
        while (!st1.empty()) hd[st1.front()] = 0, st1.pop();
    }
    void finds(int x) {
        for (int i = hd[x & 1048575]; i; i = nt[i]) {
            if (v[i] == x) a4[++ct3] = s[i];
        }
    }
} hash;
void solve(int l, int r) {
    if (l > r) return;
    int mid = (l + r) >> 1, s1 = 0, ct = 0;
    hash.init();
    for (int i = mid; i >= l; i--) s1 = (s1 + a2[i]) % mod, hash.add(s1, i);
    std::sort(fy + 1, fy + ct + 1);
    s1 = 0;
    ab[mid] = 0;
    for (int i = mid + 1; i <= r; i++) {
        int st = v[i], v2 = a2[i], tmpu;
        s1 = (s1 + a2[i]) % mod;
        if (st > ab[i - 1]) {
            ab[i] = st, a3[i] = v2, a6[i] = tmpu = a5[i];
        } else {
            ab[i] = ab[i - 1], a3[i] = a3[i - 1], a6[i] = tmpu = a6[i - 1];
        }
        for (int s = 1, v1 = a3[i]; s < 18; s++, v1 = v1 * 2 % mod) {
            int a1 = (2ll * v1 + mod - s1) % mod;
            ct3 = 0;
            hash.finds(a1);
            tmpu = 2 * tmpu % D;
            for (int j = 1; j <= ct3; j++) {
                if (check(a4[j], i, ab[i] + s, tmpu)) {
                    as1[++ct1] = a4[j] * 1000000ll + i;
                }
            }
        }
    }
    ct = 0;
    s1 = 0;
    for (int i = mid + 1; i <= r; i++) {
        s1 = (s1 + a2[i]) % mod;
        hash.add(s1, i);
    }
    s1 = 0;
    std::sort(fy + 1, fy + ct + 1);
    ab[mid + 1] = 0;
    for (int i = mid; i >= l; i--) {
        int st = v[i], v2 = a2[i], tmpu;
        s1 = (s1 + a2[i]) % mod;
        if (st > ab[i + 1]) {
            ab[i] = st, a3[i] = v2, a6[i] = tmpu = a5[i];
        } else {
            ab[i] = ab[i + 1], a3[i] = a3[i + 1], a6[i] = tmpu = a6[i + 1];
        }
        for (int s = 1, v1 = a3[i]; s < 18; s++, v1 = v1 * 2 % mod) {
            int a1 = (2ll * v1 + mod - s1) % mod;
            ct3 = 0;
            hash.finds(a1);
            tmpu = 2 * tmpu % D;
            for (int j = 1; j <= ct3; j++) {
                if (check(i, a4[j], ab[i] + s, tmpu)) {
                    as1[++ct1] = i * 1000000ll + a4[j];
                }
            }
        }
    }
    if (l == r) {
        as++;
        return;
    }
    solve(l, mid);
    solve(mid + 1, r);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        a2[i] = power(2, v[i]);
        a5[i] = pows(2, v[i], D);
    }
    for (int i = 1; i <= 1; i++) {
        for (int j = 1; j <= n; j++) {
            a1[i][j] = (a1[i][j - 1] + pows(2, v[j], ty[i])) % ty[i];
        }
    }
    solve(1, n);
    std::sort(as1 + 1, as1 + ct1 + 1);
    for (int i = 1; i <= ct1; i++) {
        if (as1[i] != as1[i - 1]) as++;
    }
    printf("%d\n", as);
}