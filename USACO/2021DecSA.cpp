#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

using int64 = long long;

const int B = 3;
const int N = 200005;

int k, n, m, Pi, Le;
int p[N], t[N], b[N], c[N];

std::pair<int, int> Sp[N];

int64 Sum, Max = -1;
int64 Val[N][B];

std::priority_queue<std::tuple<int64, int, int> > Que;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> k >> m >> n;
    for (int i = 1; i <= k; ++i) std::cin >> Sp[i].first >> Sp[i].second;
    for (int i = 1; i <= m; ++i) std::cin >> b[i];
    std::sort(Sp + 1, Sp + k + 1);
    std::sort(b + 1, b + m + 1);
    for (int i = 1; i <= k; ++i) p[i] = Sp[i].first, t[i] = Sp[i].second;
    Pi = 1;
    while (Pi <= k && p[Pi] < b[1]) Sum += t[Pi++];
    Val[0][1] = Val[0][2] = Sum, Sum = 0;
    for (int i = 1; i < m; ++i) {
        int L = b[i], R = b[i + 1], S = R - L - 1 >> 1;
        int PL = Pi;
        while (Pi <= k && p[Pi] < R) Sum += t[Pi++];
        int PR = Pi - 1, Pj = PL;
        Val[i][2] = Sum, Sum = 0;
        for (int j = PL; j <= PR; ++j) {
            while (Pj <= PR && p[Pj] <= p[j] + S) Sum += t[Pj++];
            Mad(Val[i][1], Sum), Sum -= t[j];
        }
        Sum = 0;
    }
    while (Pi <= k) Sum += t[Pi++];
    Val[m][1] = Val[m][2] = Sum, Sum = 0;
    for (int i = 0; i <= m; ++i) {
        Que.emplace(Val[i][1] * 2, i, 1);
        Que.emplace(Val[i][2], i, 2);
    }
    int Ni = 0;
    while (Ni < n) {
        auto [Add, Id, Num] = Que.top();
        Que.pop();
        if (c[Id] + Num >= B) continue;
        if (Ni == n - 1 && Num == 2) {
            if (Max != -1) Que.emplace((Add - Max) * 2, Id, 1);
            continue;
        }
        Sum += Add * Num / 2, c[Id] += Num, Ni += Num;
        Mad(Max, Val[Id][c[Id]] - Val[Id][c[Id] - 1]);
        if (c[Id] == 1) Que.emplace((Val[Id][2] - Val[Id][1]) * 2, Id, 1);
    }
    std::cout << Sum << std::endl;
    return 0;
}