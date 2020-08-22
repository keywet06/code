#include <bits/stdc++.h>
const int N = 100005;
struct node {
    int l, r;
    char v;
};
bool operator<(node a, node b) { return a.r < b.r; }
char a[N];
int n, m;
std::set<node> s;
void rd() {
    scanf("%d%d", &n, &m);
    scanf("%s", a + 1);
    for (int i = 1; i <= n; i++) {
        s.insert((node){i, i, a[i]});
    }
}
void split(std::set<node>::iterator x, int i) {
    int l = x->l, r = x->r;
    char v = x->v;
    if (i < l || i >= r) return;
    s.erase(x);
    s.insert((node){l, i, v});
    s.insert((node){i + 1, r, v});
}
int c[30];
void paix(int l, int r, bool p) {
    std::set<node>::iterator x = s.lower_bound((node){0, l - 1, 0});
    split(x, l - 1);
    std::set<node>::iterator y = s.lower_bound((node){0, r, 0});
    split(y, r);
    x = s.lower_bound((node){0, l, 0});
    y = s.lower_bound((node){0, r, 0});
    y++;
    for (std::set<node>::iterator i = x; i != y; i++)
        c[(i->v) - 'a'] += (i->r) - (i->l) + 1;
    s.erase(x, y);
    if (p) {
        int x = l;
        for (int i = 0; i <= 26; i++)
            if (c[i] > 0) {
                s.insert((node){x, x + c[i] - 1, i + 'a'});
                x += c[i];
            }
    } else {
        int x = l;
        for (int i = 26; i >= 0; i--)
            if (c[i] > 0) {
                s.insert((node){x, x + c[i] - 1, i + 'a'});
                x += c[i];
            }
    }
    memset(c, 0, sizeof(c));
}
int main() {
    rd();
    for (int i = 1; i <= m; i++) {
        int l, r, p;
        scanf("%d%d%d", &l, &r, &p);
        paix(l, r, p);
    }
    for (std::set<node>::iterator i = s.begin(); i != s.end(); i++) {
        for (int j = i->l; j <= i->r; j++) putchar(i->v);
    }
    std::cout << "\n";
    return 0;
}