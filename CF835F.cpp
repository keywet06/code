#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;

int n, m = 0, tot = 0, head[N], a[N], top = 0, sta[N];
ll fir[N], sec[N], mx[N], s0[N], s1[N], t0[N], t1[N], eVal[N];
bool vis[N], in[N];

struct Edge {
    int to, nxt;
    ll val;
} e[N << 1];

inline void add(int from, int to, ll val) {
    e[++tot].to = to;
    e[tot].val = val;
    e[tot].nxt = head[from];
    head[from] = tot;
}

template <typename T>
inline void read(T &X) {
    X = 0; char ch = 0; T op = 1;
    for(; ch > '9' || ch < '0'; ch = getchar())
        if(ch == '-') op = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        X = (X << 3) + (X << 1) + ch - 48;
    X *= op;
}

template <typename T>
inline T max(T x, T y) {
    return x > y ? x : y;
}

template <typename T>
inline T min(T x, T y) {
    return x > y ? y : x;
}

template <typename T>
inline void chkMax(T &x, T y) {
    if(y > x) x = y;
}

template <typename T>
inline void chkMin(T &x, T y) {
    if(y < x) x = y;
}

bool getCir(int x, int fat) {
    if(vis[x]) {
        for(; ; ) {
            int now = sta[top];
            in[now] = 1;
            a[++m] = now;    
            --top;    
            if(now == x) return 1;
        }
    }
    
    vis[x] = 1; sta[++top] = x;
    int tmp = top;
    for(int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if(y == fat) continue;
        if(getCir(y, x)) return 1;
        top = tmp;
    }
    
    return 0;
}

void getEval(int x, int to) {
    if(to == m + 1) return;
    for(int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if(y != a[to + 1]) continue;
        eVal[to] = e[i].val;
        getEval(y, to + 1);
    }
}

ll getMx(int x, int fat) {
    ll res = 0LL;
    for(int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if(y == fat || in[y]) continue;
        
        ll tmp = getMx(y, x), now = fir[y] + e[i].val;
        
        chkMax(res, tmp);
        if(now > fir[x]) sec[x] = fir[x], fir[x] = now;
        else if(now > sec[x]) sec[x] = now;
    }    
    chkMax(res, fir[x] + sec[x]);
    return res;
}

int main() {
    
    read(n);
    for(int i = 1; i <= n; i++) {
        int x, y; ll v;
        read(x), read(y), read(v);
        add(x, y, v), add(y, x, v);
    }
    
    getCir(1, 0);
    a[m + 1] = a[1];
    
    
    getEval(a[1], 1);
    
    
    for(int i = 1; i <= m; i++)
        mx[i] = getMx(a[i], 0);
    
    
    ll tmp = 0LL;
    for(int i = 1; i < m; i++) {
        s0[i] = max(s0[i - 1], tmp + fir[a[i]]);
        tmp += eVal[i];
    }
    
    tmp = 0LL;
    for(int i = m; i > 1; i--) {
        s1[i] = max(s1[i + 1], tmp + fir[a[i]]);
        tmp += eVal[i - 1];
    }
    
    tmp = 0LL;
    for(int i = 1; i <= m; i++) {
        t0[i] = max(t0[i - 1], max(mx[i], tmp + fir[a[i]]));
        chkMax(tmp, fir[a[i]]);
        tmp += eVal[i];
    }
    
    tmp = 0LL;
     for(int i = m; i > 1; i--) {
         t1[i] = max(t1[i + 1], max(mx[i], tmp + fir[a[i]]));
         chkMax(tmp, fir[a[i]]);
         tmp += eVal[i - 1];
    }
     
    ll ans = t0[m];
    for(int i = 1; i < m; i++)
        chkMin(ans, max(max(t0[i], t1[i + 1]), s0[i] + s1[i + 1] + eVal[m]));
    
    printf("%lld\n", ans);
    return 0;
}