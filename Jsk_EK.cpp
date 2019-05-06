const int MAX_N = 200; // 顶点数上限
const int MAX_M = 400; // 总的边数上限
const int INF = 0x3f3f3f3f; // 极大值
struct edge {
    int u, v, c, next;
} e[MAX_M];
int p[MAX_N], eid;
void init() {
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int u, int v, int c) { // 插入一条从 u 连向 v，容量为 c 的弧
    e[eid].u = u;
    e[eid].v = v;
    e[eid].c = c;
    e[eid].next = p[u];
    p[u] = eid++;
}
void addedge(int u, int v, int c) {
    insert(u, v, c);
    insert(v, u, 0); // 残量网络中的反向弧，初始容量为 0
}
int pre[MAX_N];
int S, T; // S 是源点，T 是汇点
void bfs() { // BFS 找增广路
    queue<int> q;
    q.push(S);
    memset(pre, -1, sizeof(pre));
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = p[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (pre[v] == -1 && e[i].c) {
                pre[v] = i;
                if (v == T) {
                    break;
                }
                q.push(v);
            }
        }
        if (pre[T] != -1) {
            break; // 已经找到一条增广路
        }
    }
}
int EK() {
    int ret = 0;
    while (1) {
        bfs();
        if (pre[T] == -1) {
            break; // 找不到，则已经是最大流
        }
        int Min = INF;
        for (int u = T; u != S; u = e[pre[u]].u) {
            Min = min(Min, e[pre[u]].c); // 求增广路上的最小容量
        }
        for (int u = T; u != S; u = e[pre[u]].u) {
            e[pre[u]].c -= Min; // 更新正向容量
            e[pre[u] ^ 1].c += Min; // 更新反向容量
        }
        ret += Min;
    }
    return ret;
}