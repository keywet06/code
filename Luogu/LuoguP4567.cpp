#include <algorithm>
#include <cstdio>
using namespace std;
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
const int MAXINSERTLEN = 2100000;
struct SplayTree {
    char val;
    int ch[2], fa, size, lazy;
} t[MAXINSERTLEN];
char str[MAXINSERTLEN], s[MAXINSERTLEN];
int num, root, n, len;
void pushup(int u) { t[u].size = t[t[u].ch[0]].size + t[t[u].ch[1]].size + 1; }
void pushdown(int u) {
    if (t[u].lazy) {
        t[t[u].ch[0]].lazy ^= 1;
        t[t[u].ch[1]].lazy ^= 1;
        swap(t[u].ch[0], t[u].ch[1]);
        t[u].lazy = 0;
    }
}
void rotate(int x) {
    int y = t[x].fa;
    int z = t[y].fa;
    int k = t[y].ch[1] == x;
    t[z].ch[t[z].ch[1] == y] = x;
    t[x].fa = z;
    t[y].ch[k] = t[x].ch[k ^ 1];
    t[t[x].ch[k ^ 1]].fa = y;
    t[x].ch[k ^ 1] = y;
    t[y].fa = x;
    pushup(y);
    pushup(x);
}
void Splay(int x, int goal) {
    while (t[x].fa != goal) {
        int y = t[x].fa;
        int z = t[y].fa;
        if (z != goal)
            (t[z].ch[0] == y) ^ (t[y].ch[0] == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if (goal == 0) root = x;
}
int build(int l, int r) {
    int id = ++num;
    int mid = (l + r) >> 1;
    t[id].val = str[mid];
    if (mid > l) {
        t[id].ch[0] = build(l, mid - 1);
        t[t[id].ch[0]].fa = id;
    }
    if (mid < r) {
        t[id].ch[1] = build(mid + 1, r);
        t[t[id].ch[1]].fa = id;
    }
    pushup(id);
    return id;
}
inline int findKth(int k) {
    int u = root;
    while (1) {
        pushdown(u);
        if (t[t[u].ch[0]].size >= k)
            u = t[u].ch[0];
        else if (t[t[u].ch[0]].size == k - 1)
            return u;
        else
            k -= t[t[u].ch[0]].size + 1, u = t[u].ch[1];
    }
}
char opt;
int cur;
int main() {
    n = read();
    root = cur = ++num;
    t[num].val = 1;
    t[++num].fa = cur;
    t[num].val = 1;
    t[cur].ch[1] = num;
    t[num].size = 1;
    t[cur].size = 2;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s);
        opt = s[0];
        if (opt == 'I') {
            len = read();
            for (int i = 1; i <= len; ++i) str[i] = getchar();
            Splay(findKth(cur), 0);
            Splay(findKth(cur + 1), root);
            t[t[root].ch[1]].ch[0] = (len = build(1, len));
            t[len].fa = t[root].ch[1];
            Splay(t[t[root].ch[1]].ch[0], 0);
        } else if (opt == 'G') {
            int ans = findKth(cur + 1);
            putchar(t[ans].val);
            if (t[ans].val != '\n') putchar('\n');
        } else if (opt == 'M')
            cur = read() + 1;
        else if (opt == 'P')
            --cur;
        else if (opt == 'N')
            ++cur;
        else if (opt == 'D') {
            len = read();
            Splay(findKth(cur), 0);
            Splay(findKth(t[t[root].ch[0]].size + 2 + len), root);
            t[t[root].ch[1]].ch[0] = 0;
        } else if (opt == 'R') {
            len = read();
            Splay(findKth(cur), 0);
            Splay(findKth(t[t[root].ch[0]].size + 2 + len), root);
            t[t[t[root].ch[1]].ch[0]].lazy ^= 1;
        }
    }
    return 0;
}
