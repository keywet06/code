#include <bits/stdc++.h>

const int B = 2;
const int N = 600005;

int n, q, ans, root, cnt, x, y, r, c;
int fa[N], rev[N], col[N], size[N];
int son[N][B];

std::string s;

inline void update(int u) { size[u] = size[son[u][0]] + size[son[u][1]] + 1; }

inline void pushdown(int u) {
    if (!rev[u]) return;
    if (son[u][0]) rev[son[u][0]] = !rev[son[u][0]];
    if (son[u][1]) rev[son[u][1]] = !rev[son[u][1]];
    std::swap(son[u][0], son[u][1]), rev[u] = 0;
}

inline int build(int l, int r, int f) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    fa[mid] = f, col[mid] = s[mid] - '0';
    son[mid][0] = build(l, mid - 1, mid);
    son[mid][1] = build(mid + 1, r, mid);
    update(mid);
    return mid;
}

inline int g(int u) { return son[fa[u]][1] == u; }

inline void rotate(int u) {
    // std::cerr << "rotate(" << u << ");" << std::endl;
    int t = g(u);
    pushdown(fa[u]), pushdown(u);
    if (son[fa[u]][t] = son[u][!t]) fa[son[u][!t]] = fa[u];
    son[u][!t] = fa[u];
    if (fa[u] = fa[fa[u]]) son[fa[u]][g(son[u][!t])] = u;
    fa[son[u][!t]] = u;
    if (!fa[u]) root = u;
    update(son[u][!t]), update(u);
    // std::cerr << "  fa: ";
    // for (int i = 1; i <= n; ++i) std::cout << fa[i] << ' ';
    // std::cerr << std::endl;
    // std::cerr << "lson: ";
    // for (int i = 1; i <= n; ++i) std::cout << son[i][0] << ' ';
    // std::cerr << std::endl;
    // std::cerr << "rson: ";
    // for (int i = 1; i <= n; ++i) std::cout << son[i][1] << ' ';
    // std::cerr << std::endl;
}

inline void splay(int u) {
    while (fa[u]) {
        if (fa[fa[u]]) rotate(fa[fa[fa[u]]] && g(u) == g(fa[u]) ? fa[u] : u);
        rotate(u);
    }
}

inline int find(int x) {
    int u = root;
    while (1) {
        pushdown(u);
        if (x <= size[son[u][0]]) {
            u = son[u][0];
        } else if (x > size[son[u][0]] + 1) {
            x -= size[son[u][0]] + 1;
            u = son[u][1];
        } else {
            break;
        }
    }
    splay(u);
    return u;
}

inline void color(int u) { col[u] = !col[u]; }

inline int reverse(int u) { return rev[u] = !rev[u], u; }

inline int reverse(int x, int y) {
    // std::cerr << "reverse(" << x << ", " << y << ");" << std::endl;
    if (x == 1 && y == n) {
        return reverse(root);
    } else if (x == 1) {
        return reverse(son[find(y + 1)][0]);
    } else if (y == n) {
        return reverse(son[find(x - 1)][1]);
    } else {
        find(x - 1), find(y + 1);
        // std::cout << root << " " << son[root][0] << " " << son[son[root][0]][1]
        //           << std::endl;
        return reverse(son[son[root][0]][1]);
    }
}

inline int query(int x) { return col[find(x)]; }

inline int pre(int x) { return x == 1 ? n : x - 1; }
inline int suf(int x) { return x == n ? 1 : x + 1; }

inline void print(int u) {
    if (!u) return;
    print(son[u][rev[u]]);
    std::cout << col[u];
    print(son[u][!rev[u]]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q, n *= 6;
    std::cin >> s, s = s[n - 1] + s;
    root = build(1, n, 0);
    print(root), std::cout << std::endl;
    for (int i = 0; i < n; ++i) ans += s[i] != s[i + 1];
    std::cout << ans / 2 + 1 << '\n';
    while (q--) {
        std::cin >> x >> y;
        x = ((x + r) % n + n - 1) % n + 1;
        x = ((y + r) % n + n - 1) % n + 1;
        ans -= col[query(x)] != col[query(pre(x))];
        ans -= col[query(y)] != col[query(suf(y))];
        if (x == y) {
            color(find(x));
        } else if (x < y) {
            reverse(x, y);
        } else {
            int u = reverse(x, n), v = reverse(1, y);
            std::swap(son[fa[u]][g(u)], son[fa[v]][g(v)]);
            std::swap(fa[u], fa[v]);
            if (!fa[u]) son[fa[u]][0] = 0;
            if (!fa[v]) son[fa[v]][0] = 0;
            while (u) update(u = fa[u]);
            while (u) update(v = fa[v]);
            r += -x - y + n + 1;
            c = -x - y + n + 1;
            x = ((x + c) % n + n - 1) % n + 1;
            x = ((y + c) % n + n - 1) % n + 1;
        }
        print(root), std::cout << std::endl;
        ans += col[query(x)] != col[query(pre(x))];
        ans += col[query(y)] != col[query(suf(y))];
        std::cout << ans / 2 + 1 << std::endl;
    }
    return 0;
}