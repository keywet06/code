const int MAX_N = 100;  // X �����еĶ���������
const int MAX_M = 10000;  // �ܵı�������
const int INF = 1000000000;  // ����ֵ
struct edge {
    int v, c, next;  // v ��ָ�ߵ���һ�����㣬c ��ʾ����
} e[MAX_M];
int p[MAX_N], eid;
void init() {
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int u, int v, int c) {  // ����һ���� u ���� v������Ϊ c �Ļ�
    e[eid].v = v;
    e[eid].c = c;
    e[eid].next = p[u];
    p[u] = eid++;
}
void addedge(int u, int v, int c) {  // �� insert2 �����������еĻ�
    insert(u, v, c);
    insert(v, u, 0);  // ����һ�������෴����ǰ����Ϊ 0 �Ļ�
}
int S, T;  // S ��Դ�㣬T �ǻ��
int d[MAX_N];  // �洢ÿ������Ĳ��
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

int dfs(int u, int flow) {  // flow ��ʾ��ǰ������֧����������
    if (u == T) {
        return flow;
    }
    int res = 0;
    for (int i = p[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (e[i].c > 0 && d[u] + 1 == d[v]) {
            int tmp = dfs(v, min(flow, e[i].c));  // �ݹ���㶥�� v���� c(u, v) �����µ�ǰ��������
            flow -= tmp;
            e[i].c -= tmp;
            res += tmp;
            e[i ^ 1].c += tmp;  // �޸ķ��򻡵�����
            if (flow == 0) {  // �����ﵽ���ޣ����ؼ���������
                break;
            }
        }
    }
    if (res == 0) {  // ��ǰû�о������� u �Ŀ������������������� u
        d[u] = -1;
    }
    return res;
}

int maxflow() {  // ��������ֵ����������Ľ��
    int res = 0;
    while (bfs()) {
        res += dfs(S, INF);  // ��ʼ��������Ϊ INF
    }
    return res;
}