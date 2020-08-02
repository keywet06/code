#include <bits/stdc++.h>
const int N = 505;
const int L = N * N;
const int op[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int n, m, K, cnt, nx, ny, ne, dnt, tmp, oax, oe, u;
int fa[L], max[L];
int h[N][N], vis[N][N], po[N][N];
long long nax, tum, ans;
long long val[L], sum[L], size[L];
std::pair<int, int> q[L];
std::pair<int, int> f[N][N];
std::priority_queue<long long> pq;
std::vector<int> son[L];
inline std::pair<int, int> &fb(std::pair<int, int> x) {
    return f[x.first][x.second];
}
inline std::pair<int, int> find(std::pair<int, int> x) {
    return fb(x) == x ? x : fb(x) = find(fb(x));
}
inline int cmp(std::pair<int, int> x, std::pair<int, int> y) {
    return h[x.first][x.second] <= h[y.first][y.second];
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> K;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> h[i][j];
            po[i][j] = ++cnt;
            q[cnt] = std::make_pair(i, j);
            f[i][j] = std::make_pair(i, j);
            max[cnt] = h[i][j];
            size[cnt] = 1;
            oax = std::max(oax, h[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            tum += oax - h[i][j];
        }
    }
    std::sort(q + 1, q + m * n + 1, cmp);
    for (int i = 1; i <= m * n; ++i) {
        std::set<std::pair<int, int> > set;
        vis[q[i].first][q[i].second] = 1;
        for (int j = 0; j < 4; ++j) {
            nx = q[i].first + op[j][0];
            ny = q[i].second + op[j][1];
            if (!vis[nx][ny]) continue;
            set.insert(find(std::make_pair(nx, ny)));
        }
        oe = po[q[i].first][q[i].second];
        for (std::set<std::pair<int, int> >::iterator it = set.begin();
             it != set.end(); ++it) {
            ne = po[it->first][it->second];
            son[oe].push_back(ne);
            fa[ne] = oe;
            size[oe] += size[ne];
            val[ne] = (max[oe] - max[ne]) * size[ne];
            fb(*it) = q[i];
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        nax = 0;
        u = po[q[i].first][q[i].second];
        for (std::vector<int>::iterator it = son[u].begin(); it != son[u].end();
             ++it) {
            if (sum[*it] > nax) {
                nax = sum[*it];
                tmp = *it;
            }
        }
        sum[u] = val[u] + nax;
        for (std::vector<int>::iterator it = son[u].begin(); it != son[u].end();
             ++it) {
            if (*it == tmp) continue;
            pq.push(sum[*it]);
        }
    }
    pq.push(sum[po[q[cnt].first][q[cnt].second]]);
    for (int i = 1; i <= K; ++i) {
        tum -= pq.empty() ? 0 : pq.top();
        if (!pq.empty()) pq.pop();
        ans ^= tum;
    }
    std::cout << ans << std::endl;
    return 0;
}