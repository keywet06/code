#include<bits/stdc++.h>
const int inf = 123456789;
inline int read() {
    register int x = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
const int maxn = 10005;
struct node{
    double x, y;
};
node e[maxn];
int n, st[maxn], top;
double ans;
template<typename T> inline T sqr(T x) {
    return x * x;
}
inline bool cmp(node a, node b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
inline double dis(int x, int y) {
    return sqrt(sqr(e[x].x - e[y].x) + sqr(e[x].y - e[y].y));
}
inline double getk(int x, int y) {
    return e[x].x == e[y].x ? inf : (e[x].y - e[y].y) / (e[x].x - e[y].x);
}
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        scanf("%lf %lf", &e[i].x, &e[i].y);
    }
    std::sort(e + 1, e + n + 1, cmp);
    for (int i = 1; i <= n; ++i) {
        st[++top] = i;
        while(top > 2 && getk(st[top], st[top - 2]) < getk(st[top - 1], st[top - 2])) {
            st[top - 1] = st[top];
            --top;
        }
    }
    for (int i = 1; i < top; ++i) {
        ans += dis(st[i], st[i + 1]);
    }
    top = 0;
    for (int i = n; i; --i) {
        st[++ top] = i;
        while(top > 2 && getk(st[top], st[top - 2]) < getk(st[top - 1], st[top - 2])) {
            st[top - 1] = st[top];
            --top;
        }
    }
    for (int i = 1; i < top; ++i) {
        ans += dis(st[i], st[i + 1]);
    }
    printf("%.2lf", ans);
    return 0;
}