/*
        By keywet06
        Data:2018/09/02
        Source:luogu(https://www.luogu.org/)P1744
        Tittle:采购特价商品
        Code-key:fast
        Use:Dev-C++
*/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
const double INF = 1e8;
const int maxN = 100;
double juli, x, y;
double dx[maxN + 5], dy[maxN + 5];
double floyd[maxN + 5][maxN + 5];
int m, n, s, t;
void init() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            floyd[i][j] = INF;
        }
    }
    return;
}
void insert(int i, int j) {
    x = abs(dx[i] - dx[j]);
    y = abs(dy[i] - dy[j]);
    juli = sqrt(x * x + y * y);
    if (juli < floyd[i][j]) {
        floyd[i][j] = juli;
        floyd[j][i] = juli;
    }
    return;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &dx[i], &dy[i]);
    }
    init();
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int xx, yy;
        scanf("%d %d", &xx, &yy);
        insert(xx - 1, yy - 1);
    }
    scanf("%d %d", &s, &t);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                x = floyd[i][k] + floyd[k][j];
                if (x < floyd[i][j]) {
                    floyd[i][j] = x;
                }
            }
        }
    }
    printf("%.2lf\n", floyd[s - 1][t - 1]);
    return 0;
}
