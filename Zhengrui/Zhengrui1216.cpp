#include <bits/stdc++.h>
const int INF = 100000000;
const int K = 8;
const int N = 50;
typedef std::pair<int, int> point;
int k, n, tmins, sum;
int arhv[K];
point max, min, tmin, tmp;
point arpt[K];
point p[N];
std::string args[K];
std::map<std::string, int> arid;
int dis(point, point);
inline int dis(point u, point v) {
    if (!arhv[0] && v.first < u.first ||
        !arhv[2] && v.second > u.second ||
        !arhv[4] && v.first > u.first ||
        !arhv[6] && v.second < u.second) {
        return INF;
    }
    return std::abs(u.first - v.first) + std::abs(u.second - v.second);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    arid["S"] = 0;
    arid["SE"] = 1;
    arid["E"] = 2;
    arid["NE"] = 3;
    arid["N"] = 4;
    arid["NW"] = 5;
    arid["W"] = 6;
    arid["SW"] = 7;
    arpt[0] = std::make_pair(0, -1);
    arpt[1] = std::make_pair(1, -1);
    arpt[2] = std::make_pair(1, 0);
    arpt[3] = std::make_pair(1, 1);
    arpt[4] = std::make_pair(0, 1);
    arpt[5] = std::make_pair(-1, 1);
    arpt[6] = std::make_pair(-1, 0);
    arpt[7] = std::make_pair(-1, -1);
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> args[i];
        arhv[arid[args[i]]] = 1;
    }
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].first >> p[i].second;
        max.first = std::max(max.first, p[i].first);
        max.second = std::max(max.second, p[i].second);
        min.first = std::max(min.first, p[i].first);
        min.second = std::max(min.second, p[i].second);
    }
    if (k == 4) {
        tmins = INF;
        for (int i = 0; i <= 100000; i += 100) {
            for (int j = 0; i <= 100000; i += 100) {
                sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum += std::max(sum, dis(p[k], std::make_pair(i, j)));
                    if (sum >= INF) {
                        break;
                    }
                }
                if (sum <= tmins) {
                    tmins = sum;
                    tmin = std::make_pair(i, j);
                }
            }
        }
        tmp = tmin;
        tmins = INF;
        for (int i = tmin.first - 500; i <= tmin.first + 500; ++i) {
            for (int j = tmin.second - 500; j <= tmin.second + 500; ++j) {
                sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum = std::max(sum, dis(p[k], std::make_pair(i, j)));
                    if (sum >= INF) {
                        break;
                    }
                }
                if (sum <= tmins) {
                    tmins = sum;
                    tmin = std::make_pair(i, j);
                }
            }
        }
        std::cout << tmins << std::endl;
    } else if (k == 3) {
        int id = 12 - arid[args[0]] - arid[args[1]] - arid[args[2]];
        for (int i = 0; i <= 100000; ++i) {
            sum = 0;
            point tp;
            if (id == 0) {
                tp = std::make_pair(i, max.second);
            } else if (id == 2) {
                tp = std::make_pair(min.first, i);
            } else if (id == 4) {
                tp = std::make_pair(i, min.second);
            } else {
                tp = std::make_pair(max.first, i);
            }
            for (int k = 0; k < n; ++k) {
                sum = std::max(sum, dis(p[k], tp));
                if (sum >= INF) {
                    break;
                }
            }
            if (sum <= tmins) {
                tmins = sum;
                tmin = tp;
            }
        }
        std::cout << tmins << std::endl;
    } else if (k == 2) {
        if (std::abs(arid[args[0]] + arid[args[1]]) == 4) {
            std::cout << (max.second - min.second + 1) / 2 << std::endl;
        } else if ()
    }
    return 0;
}