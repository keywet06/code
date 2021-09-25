#include <bits/stdc++.h>

#define pub push_back
#define pob pop_back

using int64 = long long;

const int N = 1005;
const int K = 10;

struct point {
    int x, y;
};

std::istream &operator>>(std::istream &out, point &p) {
    return out >> p.x >> p.y;
}

int n, m;
int via[K];
int vib[N];

point pa[K];
point pb[N];

std::vector<int> q;
std::vector<int> bar[N][K];

bool in(point x, point u, point v) {
    return int64(u.x - x.x) * (v.y - x.y) == int64(u.y - x.y) * (v.x - x.x) &&
           (x.x <= u.x && x.x >= v.x || x.x >= u.x && x.x <= v.x) &&
           (x.y <= u.y && x.y >= v.y || x.y >= u.y && x.y <= v.y);
}

inline bool dfs(int c) {
    if (c == q.size()) return true;
    int f, u = q[c], cur = q.size();
    vib[u] = 2;
    for (int v = 0; v < m; ++v) {
        if (via[v] || bar[u][v].size() > m) continue;
        f = 0;
        for (int x : bar[u][v]) {
            if (!vib[x]) vib[x] = 1, q.pub(x);
            // if (vib[x] == 2 && (f = 1)) break;
        }
        if (f || q.size() > m) {
            while (q.size() > cur) vib[q.back()] = 0, q.pob();
            continue;
        }
		via[v] = 1;
        if (dfs(c + 1)) return true;
		via[v] = 0;
        while (q.size() > cur) vib[q.back()] = 0, q.pob();
    }
    vib[u] = 1;
    return false;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> m >> n;
    for (int i = 0; i < m; ++i) std::cin >> pa[i];
    for (int i = 0; i < n; ++i) std::cin >> pb[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                if (i == k || !in(pb[k], pb[i], pa[j])) continue;
                bar[i][j].pub(k);
                if (bar[i][j].size() > m) break;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        memset(via, 0, sizeof(via));
        memset(vib, 0, sizeof(vib));
        q.clear(), q.pub(i);
        std::cout << int(dfs(0));
    }
    std::cout << '\n';
    return 0;
}