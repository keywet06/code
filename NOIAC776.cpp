#include <bits/stdc++.h>
const int N = 100005;
int cnt, n, opt, m, flag;
int del[N];
std::string x, y, lx, ly, llx, lly;
std::string name[N];
std::map<std::string, int> vis;
int id(std::string);
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    for (int T = 1; T <= n; ++T) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y;
            name[id(x)] = x;
            if (x == lx && y == ly && x == llx && y == lly) {
                ++del[id(x)];
            }
            if (y == (std::string)("thanks") && del[id(lx)]) {
                --del[id(lx)];
            }
            llx = lx;
            lly = ly;
            lx = x;
            ly = y;
        } else {
            std::cin >> m;
            for (int i = 1; i <= m; ++i) {
                std::cin >> x;
                if (del[id(x)]) {
                    --del[id(x)];
                }
            }
        }
    }
    std::sort(name + 1, name + cnt + 1);
    for (int i = 1; i <= cnt; ++i) {
        if (del[id(name[i])]) {
            flag = 1;
            std::cout << name[i] << " " << del[id(name[i])] << std::endl;
        }
    }
    if (!flag) {
        printf("None\n");
    }
    return 0;
}
inline int id(std::string x) { return vis[x] ? vis[x] : vis[x] = ++cnt; }