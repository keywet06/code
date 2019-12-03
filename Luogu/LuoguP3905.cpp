/*
        By keywet06
        Data:2018/09/02
        Source:luogu(https://www.luogu.org/)P39050
        Tittle:道路重建
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
int d, juli, x, y, m, n, s, t;
int dx[maxN + 5], dy[maxN + 5];
int floyd[maxN + 5][maxN + 5];
void init() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            floyd[i][j] = INF;
        }
    }
    return;
}
void insert(int i, int j, int k) {
    if (k < floyd[i][j]) {
        floyd[i][j] = k;
        floyd[j][i] = k;
    }
    return;
}
void init2() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (floyd[i][j] < 0) {
                floyd[i][j] *= -1;
            } else if (floyd[i][j] < INF) {
                floyd[i][j] = 0;
            }
        }
    }
    return;
}
int main() {
    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int xx, yy, zz;
        scanf("%d %d %d", &xx, &yy, &zz);
        insert(xx - 1, yy - 1, zz);
    }
    init();
    scanf("%d", &d);
    for (int i = 0; i < d; ++i) {
        int xx, yy;
        scanf("%d %d", &xx, &yy);
        floyd[xx - 1][yy - 1] *= -1;
    }
    init2();
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
    printf("%d\n", floyd[s - 1][t - 1]);
    return 0;
}
