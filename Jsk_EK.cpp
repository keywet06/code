const int MAX_N = 200; // ����������
const int MAX_M = 400; // �ܵı�������
const int INF = 0x3f3f3f3f; // ����ֵ
struct edge {
    int u, v, c, next;
} e[MAX_M];
int p[MAX_N], eid;
void init() {
    memset(p, -1, sizeof(p));
    eid = 0;
}
void insert(int u, int v, int c) { // ����һ���� u ���� v������Ϊ c �Ļ�
    e[eid].u = u;
    e[eid].v = v;
    e[eid].c = c;
    e[eid].next = p[u];
    p[u] = eid++;
}
void addedge(int u, int v, int c) {
    insert(u, v, c);
    insert(v, u, 0); // ���������еķ��򻡣���ʼ����Ϊ 0
}
int pre[MAX_N];
int S, T; // S ��Դ�㣬T �ǻ��
void bfs() { // BFS ������·
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
            break; // �Ѿ��ҵ�һ������·
        }
    }
}
int EK() {
    int ret = 0;
    while (1) {
        bfs();
        if (pre[T] == -1) {
            break; // �Ҳ��������Ѿ��������
        }
        int Min = INF;
        for (int u = T; u != S; u = e[pre[u]].u) {
            Min = min(Min, e[pre[u]].c); // ������·�ϵ���С����
        }
        for (int u = T; u != S; u = e[pre[u]].u) {
            e[pre[u]].c -= Min; // ������������
            e[pre[u] ^ 1].c += Min; // ���·�������
        }
        ret += Min;
    }
    return ret;
}