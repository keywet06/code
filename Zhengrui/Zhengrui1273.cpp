#include <bits/stdc++.h>
const int N = 10000;
const int Np = N + 5;
double z;
int T, n, m, x, y, flag;
int lx[Np], ly[Np], ok[Np];
std::pair<std::pair<int, int>, double> a, b, c;
std::queue<int> calc;
std::vector<std::pair<int, double> > to[Np];
std::vector<std::pair<std::pair<int, int>, double> > ad[Np];
int toint(double x);
inline int toint(double x) { return x + 0.5; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        memset(lx, 0, sizeof(lx));
        memset(ly, 0, sizeof(ly));
        memset(ok, 0, sizeof(ok));
        std::cin >> n >> m;
        std::cin >> x >> y >> z;
        lx[2] = toint(z);
        ok[1] = ok[2] = 1;
        for (int i = 2; i <= m; ++i) {
            std::cin >> x >> y >> z;
            to[x].push_back(std::make_pair(y, z));
            to[y].push_back(std::make_pair(x, z));
        }
        for (std::pair<int, double> v : to[1]) {
            ad[v.first].push_back(
                std::make_pair(std::make_pair(lx[1], ly[1]), v.second));
            if (ad[v.first].size() == 2) {
                calc.push(v.first);
            }
        }
        for (std::pair<int, double> v : to[2]) {
            ad[v.first].push_back(
                std::make_pair(std::make_pair(lx[2], ly[2]), v.second));
            if (ad[v.first].size() == 2) {
                calc.push(v.first);
            }
        }
        while (!calc.empty()) {
            int u = calc.front();
            ok[u] = 1;
            calc.pop();
            a = ad[u][0];
            b = ad[u][1];
            if (flag = ad[u].size() > 2) {
                c = ad[u][2];
            }
        }
        for (int i = 1; i <= n; ++i) {
            to[i].clear();
        }
    }
    return 0;
}