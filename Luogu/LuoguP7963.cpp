#include <bits/stdc++.h>

const int N = 2000005;
const int M = 5000005;
const int R = M - 1;
const int ro[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct point {
    int col, lv;
    point() : col(0), lv(0) {}
    point(int _col, int _lv) : col(_col), lv(_lv) {}
};

inline bool operator>(point x, point y) {
    return y.col == -1 || x.col != y.col && x.lv >= y.lv;
}

struct tvec {
    int a[4];
    tvec() { memset(a, 0, sizeof(a)); }
    int &operator[](size_t x) { return a[x]; }
};

struct node {
    int sz, ls, rs;
    node() : sz(0), ls(0), rs(0) {}
    node(int _sz, int _ls, int _rs) : sz(_sz), ls(_ls), rs(_rs) {}
};

using tree = std::vector<node>;

int f[5][N], r[N], rtr[N], pc[N], pl[N], px[N], py[N], rt[2][N], ans[N];

tree t, trg, tr[2];

std::stack<int> st;

inline int ffd(int *f, int x) { return f[x] = f[x] == x ? x : ffd(f, f[x]); }
inline int &fd(int c, int x) { return f[c][ffd(f[c], x)]; }

inline void insert(tree &tr, int &u, int l, int r, int x, int y) {
    if (!u) u = ++tr[R].sz;
    tr[u].sz += y;
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) {
        insert(tr, tr[u].ls, l, mid, x, y);
    } else {
        insert(tr, tr[u].rs, mid + 1, r, x, y);
    }
}

inline int find(tree &tr, int u, int l, int r, int x, int y) {
    if (!tr[u].sz) return 0;
    if (l >= x && r <= y) return tr[u].sz;
    int mid = l + r >> 1, ret = 0;
    if (x <= mid) ret += find(tr, tr[u].ls, l, mid, x, y);
    if (y > mid) ret += find(tr, tr[u].rs, mid + 1, r, x, y);
    return ret;
}

inline void merge(tree &tr, int &u, int v, int l, int r) {
    if (tr[u].sz < tr[v].sz) std::swap(u, v);
    if (!tr[v].sz) return;
    if (l == r) return void(tr[u].sz += tr[v].sz);
    int mid = l + r >> 1;
    merge(tr, tr[u].ls, tr[v].ls, l, mid);
    merge(tr, tr[u].rs, tr[v].rs, mid + 1, r);
    tr[u].sz = tr[tr[u].ls].sz + tr[tr[u].rs].sz;
}

inline void mergeS(tree &tr, int &u, int v, int l, int r) {
    if (tr[u].sz < tr[v].sz) std::swap(u, v);
    if (!tr[v].sz) return;
    if (l == r) return (tr[u].sz += tr[v].sz) > 1 ? st.push(l) : void(0);
    int mid = l + r >> 1;
    mergeS(tr, tr[u].ls, tr[v].ls, l, mid);
    mergeS(tr, tr[u].rs, tr[v].rs, mid + 1, r);
    tr[u].sz = tr[tr[u].ls].sz + tr[tr[u].rs].sz;
}

int n, m, q, w, k;

std::string s;

std::vector<std::vector<point> > p;

std::vector<std::vector<tvec> > ed;

inline int g(int x, int y) { return x * m + y; }
inline int gr(int x, int y) { return y * n + x; }
inline int gx(int x) { return x / m; }
inline int gy(int x) { return x % m; }
inline int rot(int x) { return gr(gx(x), gy(x)); }

inline void merge(int &u, int &v) {
    if (u == v) return;
    mergeS(t, r[u], r[v], 0, w - 1);
    merge(trg, rtr[u], rtr[v], 0, w - 1);
    merge(tr[0], rt[0][u], rt[0][v], 1, k);
    merge(tr[1], rt[1][u], rt[1][v], 1, k);
    while (!st.empty()) {
        int x = gx(st.top()), y = gy(st.top()), c = p[x][y].col;
        st.pop();
        insert(t, r[u], 0, w - 1, g(x, y), -1);
        insert(trg, rtr[u], 0, w - 1, gr(x, y), -1);
        insert(tr[c], rt[c][u], 1, k, p[x][y].lv, -1);
    }
    v = u;
}

int Main() {
    t.clear(), trg.clear(), tr[0].clear(), tr[1].clear();
    t.emplace_back(), trg.emplace_back(), tr[0].emplace_back(),
        tr[1].emplace_back();
    t.resize(M), trg.resize(M), tr[0].resize(M), tr[1].resize(M);
    std::cin >> n >> m >> q, w = n * m, k = q + 1;
    p = decltype(p)(n, std::vector<point>(m, point(-1, q + 1)));
    ed = decltype(ed)(n, std::vector<tvec>(m));
    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        for (int j = 0; j < m - 1; ++j) {
            ed[i][j][0] = ed[i][j + 1][2] = s[j] - '0';
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> s;
        for (int j = 0; j < m; ++j) {
            ed[i][j][1] = ed[i + 1][j][3] = s[j] - '0';
        }
    }
    for (int i = 1, col, lv, x, y; i <= q; ++i) {
        std::cin >> col >> lv >> x >> y, --x, --y;
        p[x][y] = point(col, lv);
        pc[i] = col, pl[i] = lv, px[i] = x, py[i] = y;
    }
    for (int i = 0; i < w; ++i) {
        f[0][i] = f[1][i] = f[2][i] = f[3][i] = f[4][i] = i;
        r[i] = rt[0][i] = rt[1][i] = rtr[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (p[i][j].col == -1) continue;
            int &x = p[i][j].col, nx, ny;
            for (int z = 0; z < 4; ++z) {
                nx = i + ro[z][0], ny = j + ro[z][1];
                if (ed[i][j][z] != 3 || p[nx][ny].col != -1) continue;
                insert(t, r[g(nx, ny)], 0, w - 1, g(i, j), 1);
                insert(trg, rtr[g(nx, ny)], 0, w - 1, gr(i, j), 1);
                insert(tr[x], rt[x][g(nx, ny)], 1, k, p[i][j].lv, 1);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            insert(t, r[g(i, j)], 0, w - 1, g(i, j), 1);
            insert(trg, rtr[g(i, j)], 0, w - 1, gr(i, j), 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (p[i][j].col != -1) continue;
            for (int z = 0, nx, ny; z < 4; ++z) {
                if (ed[i][j][z] < 2) continue;
                nx = i + ro[z][0], ny = j + ro[z][1];
                if (p[nx][ny].col != -1) continue;
                if (ed[i][j][z] == 2) {
                    fd(z, g(i, j)) = fd(z, g(nx, ny));
                } else {
                    merge(fd(4, g(i, j)), fd(4, g(nx, ny)));
                }
            }
        }
    }
    for (int c = q; c; --c) {
        int x = px[c], y = py[c], col = pc[c], lv = pl[c], id = g(x, y);
        point d = p[x][y];
        int nx, ny, u = fd(4, id);
        for (int z = 0; z < 4; ++z) {
            nx = x + ro[z][0], ny = y + ro[z][1];
            if (ed[x][y][z] != 3 || p[nx][ny].col != -1) continue;
            int a = fd(4, g(nx, ny));
            if (u != a) {
                insert(tr[col], rt[col][a], 1, k, lv, -1);
                insert(t, r[a], 0, w - 1, id, -1);
                insert(trg, rtr[a], 0, w - 1, gr(x, y), -1);
                merge(fd(4, u), fd(4, a));
            }
        }
        for (int z = 0; z < 4; ++z) {
            nx = x + ro[z][0], ny = y + ro[z][1];
            if (ed[x][y][z] != 3 || p[nx][ny].col == -1) continue;
            if (find(t, r[u], 0, w - 1, g(nx, ny), g(nx, ny))) continue;
            int col = p[nx][ny].col, lv = p[nx][ny].lv;
            insert(t, r[u], 0, w - 1, g(nx, ny), 1);
            insert(trg, rtr[u], 0, w - 1, gr(nx, ny), 1);
            insert(tr[col], rt[col][u], 1, k, lv, 1);
        }
        int ret = find(t, r[u], 0, w - 1, 0, w - 1);
        ret -= find(tr[col], rt[col][u], 1, k, 1, k);
        ret -= find(tr[!col], rt[!col][u], 1, k, lv + 1, k);
        for (int z = 0, o; o = (z + 2) % 4, z < 4; ++z) {
            nx = x + ro[z][0], ny = y + ro[z][1];
            if (ed[x][y][z] != 2 || p[nx][ny].col != -1) continue;
            fd(z, g(x, y)) = fd(z, g(nx, ny));
            fd(o, g(nx, ny)) = fd(o, g(x, y));
        }
        int sl = fd(2, g(x, y)), sr = fd(0, g(x, y)), su = fd(3, g(x, y)),
            sd = fd(1, g(x, y));
        if (ed[x][gy(sl)][2] == 2 && d > p[x][gy(sl) - 1]) --sl;
        if (ed[x][gy(sr)][0] == 2 && d > p[x][gy(sr) + 1]) ++sr;
        if (ed[gx(su)][y][3] == 2 && d > p[gx(su) - 1][y]) su -= m;
        if (ed[gx(sd)][y][1] == 2 && d > p[gx(sd) + 1][y]) sd += m;
        su = rot(su), sd = rot(sd);
        ret += sr - sl + 1 - find(t, r[u], 0, w - 1, sl, sr);
        ret += sd - su + 1 - find(trg, rtr[u], 0, w - 1, su, sd);
        for (int z = 0; z < 4; ++z) {
            nx = x + ro[z][0], ny = y + ro[z][1];
            if (ed[x][y][z] != 1 || !(d > p[nx][ny])) continue;
            ret += !find(t, r[u], 0, w - 1, g(nx, ny), g(nx, ny));
        }
        ans[c] = --ret;
        p[x][y] = point(-1, q + 1);
    }
    for (int i = 1; i <= q; ++i) std::cout << ans[i] << '\n';
    return 0;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int T;
    std::cin >> T;
    while (T--) Main();
    return 0;
}
