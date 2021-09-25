#include <bits/stdc++.h>

const int B = 2;
const int C = 800;
const int N = 200006;
const int M = 10000005;
const int O = N << 2;
const int INF = int(1e9);

struct node {
    int from, to, nxt, c;
};

char s[M];

int n, cnt = 1, ent = 1, S, T;
int h, t;
int que[N], head1[N], head2[N], deep[N];
int ed[M], fail[M];
int ch[M][B];

node edge[O];

std::vector<int> pos[C];

std::bitset<C> f[C];

void insert(int from, int to, int c) {
    edge[++ent] = (node){from, to, head2[from], c};
    head2[from] = ent;
}

void addedge(int from, int to, int c) {
    insert(from, to, c);
    insert(to, from, 0);
}

bool bfs() {
    h = t = 0;
    que[t++] = S;
    for (int i = 0; i <= T; ++i) deep[i] = 0;
    deep[S] = 1;
    while (h != t) {
        int cur = que[h++];
        h %= N;=
        for (int i = head2[cur]; i; i = edge[i].nxt) {
            int to = edge[i].to;
            if (!deep[to] && edge[i].c) {
                deep[to] = deep[cur] + 1;
                que[t++] = to;
                t %= N;
            }
        }
    }
    return deep[T];
}

int dfs(int x, int flow) {
    if (x == T) return flow;
    int ret = 0;
    for (int &i = head1[x]; i; i = edge[i].nxt) {
        int to = edge[i].to;
        if (deep[to] == deep[x] + 1 && edge[i].c) {
            int tmp = dfs(to, std::min(flow, edge[i].c));
            edge[i].c -= tmp, edge[i ^ 1].c += tmp;
            flow -= tmp, ret += tmp;
            if (!flow) break;
        }
    }
    if (!ret) deep[x] = 0;
    return ret;
}

int dinic() {
    int ret = 0;
    while (bfs()) {
        memcpy(head1, head2, sizeof(head2));
        ret += dfs(S, INF);
    }
    return ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int x = 1; x <= n; x++) {
        std::cin >> s;
        int p = int(strlen(s)), cur = 1;
        for (int i = 0; i < p; ++i) {
            if (!ch[cur][s[i] - 'a']) ch[cur][s[i] - 'a'] = ++cnt;
            cur = ch[cur][s[i] - 'a'];
            pos[x].push_back(cur);
        }
        ed[cur] = x;
    }
    std::queue<int> q;
    ch[0][0] = ch[0][1] = 1, q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (!ed[x]) ed[x] = ed[fail[x]];
        for (int i = 0; i < B; ++i) {
            if (!ch[x][i]) {
                ch[x][i] = ch[fail[x]][i];
            } else {
                fail[ch[x][i]] = ch[fail[x]][i];
                q.push(ch[x][i]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 1;
        for (auto x : pos[i]) {
            if (ed[x]) f[i][ed[x]] = 1;
        }
        if (ed[fail[pos[i].back()]]) f[i][ed[fail[pos[i].back()]]] = 1;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (f[i][k]) f[i] |= f[k];
        }
    }
    S = n * 2 + 1, T = n * 2 + 2;
    for (int i = 1; i <= n; ++i) addedge(S, i, 1), addedge(i + n, T, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && f[i][j]) addedge(i, j + n, 1);
        }
    }
    std::cout << n - dinic() << '\n';
    for (int i = 1; i <= n; ++i) {
        if (deep[i] && !deep[i + n]) std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}