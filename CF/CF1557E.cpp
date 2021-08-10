#include <bits/stdc++.h>
 
#define fi first
#define se second
#define mkp std::make_pair
 
using int64 = long long;
using pair = std::pair<int, int>;
 
const int F = 8;
const int N = F + 5;
const int L = 100;
 
int T, sx, sy, d, tx, ty, num, rx, ry, c, e;
int use[N][N], px[N][N], py[N][N];
 
pair st;
 
std::string re;
 
std::map<std::string, pair> map;
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    srand(time(NULL));
    std::cin >> T;
    map["Up-Left"] = mkp(-1, -1);
    map["Up"] = mkp(-1, 0);
    map["Up-Right"] = mkp(-1, 1);
    map["Left"] = mkp(0, -1);
    map["Right"] = mkp(0, 1);
    map["Down-Left"] = mkp(1, -1);
    map["Down"] = mkp(1, 0);
    map["Down-Right"] = mkp(1, 1);
    while (T--) {
        sx = sy = tx = ty = 1, d = c = 0;
        std::cout << sx << ' ' << sy << std::endl;
        std::cin >> re;
        if (re == "Done") continue;
        while (1) {
            e = 1, d = 0, c = map[re].fi == 1;
            while (e && !c && !d) {
                e = 0;
                if (sy != 1) {
                    sy = 1;
                    std::cout << sx << ' ' << sy << std::endl;
                    std::cin >> re;
                    if (re == "Done" && (d == 1)) break;
                    if (map[re].fi == 1 && (c = 1)) break;
                    if (map[re].fi == -1) e = 1;
                }
                for (sy = 2; sy <= 8; ++sy) {
                    std::cout << sx << ' ' << sy << std::endl;
                    std::cin >> re;
                    if (re == "Done" && (d = 1)) break;
                    if (map[re].fi == 1 && (c = 1)) break;
                    if (map[re].fi == -1) e = 1;
                }
            }
            if (d) break;
            ++sx;
            std::cout << sx << ' ' << sy << std::endl;
            std::cin >> re;
            if (re == "Done") break;
        }
    }
    return 0;
}
