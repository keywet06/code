const int MAX_N = 100;  // X 集合中的顶点数上限
const int MAX_M = 10000;  // 总的边数上限
const int INF = 1000000000;  // 极大值
struct edge {
    int v, c, next;  // v 是指边的另一个顶点，c 表示容量
} e[MAX_M];
int p[MAX_N], eid;
void init() {
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int u, int v, int c) {  // 插入一条从 u 连向 v，容量为 c 的弧
    e[eid].v = v;
    e[eid].c = c;
    e[eid].next = p[u];
    p[u] = eid++;
}
void addedge(int u, int v, int c) {  // 用 insert2 来插入网络中的弧
    insert(u, v, c);
    insert(v, u, 0);  // 插入一条方向相反、当前容量为 0 的弧
}
int S, T;  // S 是源点，T 是汇点
int d[MAX_N];  // 存储每个顶点的层次
bool bfs() {
    memset(d, -1, sizeof(d));
    queue<int> q;
    
    q.push(S);
    d[S] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = p[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (e[i].c > 0 && d[v] == -1) {
                q.push(v);
                d[v] = d[u] + 1;
            }
        }
    }
    return (d[T] != -1);
}

int dfs(int u, int flow) {  // flow 表示当前搜索分支的流量上限
    if (u == T) {
        return flow;
    }
    int res = 0;
    for (int i = p[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (e[i].c > 0 && d[u] + 1 == d[v]) {
            int tmp = dfs(v, min(flow, e[i].c));  // 递归计算顶点 v，用 c(u, v) 来更新当前流量上限
            flow -= tmp;
            e[i].c -= tmp;
            res += tmp;
            e[i ^ 1].c += tmp;  // 修改反向弧的容量
            if (flow == 0) {  // 流量达到上限，不必继续搜索了
                break;
            }
        }
    }
    if (res == 0) {  // 当前没有经过顶点 u 的可行流，不再搜索顶点 u
        d[u] = -1;
    }
    return res;
}

int maxflow() {  // 函数返回值就是最大流的结果
    int res = 0;
    while (bfs()) {
        res += dfs(S, INF);  // 初始流量上限为 INF
    }
    return res;
}