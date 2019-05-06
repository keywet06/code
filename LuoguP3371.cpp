/*
    By keywet06
    Code-key:test
*/
#include <cstdio>
#include <queue>
using namespace std;
#define MAX 500005
long long n, m, s, f, g, w, cnt;
long long dis[MAX], vis[MAX], next[MAX], head[MAX], zhi[MAX], quan[MAX];
void insert(long long insert_f, long long insert_g, long long insert_w);
void spfa();
int main() {
    scanf("%lld %lld %lld", &n, &m, &s);
    for (int i = 1; i <= m; ++i) {
        scanf("%lld %lld %lld", &f, &g, &w);
        insert(f, g, w);
    }
    spfa();
    for (int i = 1; i <= n; ++i) {
        printf("%lld ", dis[i]);
    }
    return 0;
}
void insert(long long insert_f, long long insert_g, long long insert_w) {
    ++cnt;
    next[cnt] = head[insert_f];
    head[insert_f] = cnt;
    zhi[cnt] = insert_g;
    quan[cnt] = insert_w;
}
void spfa() {
    for (int i = 1; i <= n; ++i) {
        dis[i] = 2147483647;
        vis[i] = 1;
    }
    dis[s] = 0;
    queue<long long> q;
    q.push(s);
    vis[s] = 0;
    while (!q.empty()) {
        long long u = q.front();
        q.pop();
        vis[u] = 1;
        for (int i = head[u]; i; i = next[i]) {
            long long v = zhi[i];
            if (dis[u] + quan[i] < dis[v]) {
                dis[v] = dis[u] + quan[i];
                if (vis[v]) {
                    vis[v] = 0;
                    q.push(v);
                }
            }
        }
    }
}
