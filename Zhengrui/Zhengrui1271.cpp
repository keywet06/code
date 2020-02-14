#include <bits/stdc++.h>
const int K = 3;
const int N = 60000;
int n, q, x, cnt, tp;
int y[N];
std::string str;
std::string now[3];
std::string name[N][K];
int pd(std::string x, std::string y);
inline int pd(std::string x, std::string y) {
    return x.substr(0, y.size()) == y;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> name[i][0] >> name[i][1] >> name[i][2];
        y[i] = i;
    }
    cnt = n;
    std::cin >> q;
    for (int i = 1; i <= q; ++i) {
        std::cin >> str >> x;
        --x;
        if (str == "+") {
            std::cin >> str;
            tp = 0;
            for (int i = 0; i < cnt; ++i) {
                if (name[y[i]][x].size() > now[x].size() &&
                    name[y[i]][x][now[x].size()] == str[0]) {
                    y[tp++] = y[i];
                }
            }
            now[x] += str;
            cnt = tp;
            std::cout << cnt << std::endl;
        } else {
            now[x].pop_back();
            cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (pd(name[i][0], now[0]) && pd(name[i][1], now[1]) &&
                    pd(name[i][2], now[2])) {
                    y[cnt++] = i;
                }
            }
            std::cout << cnt << std::endl;
        }
    }
    return 0;
}