#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;
const int M = 20005;
const int D = 10001;

int n, m;
int Fen[M];
int64 Ansl[M], Ansr[M];
std::pair<int, int> Points[N];
std::tuple<int, int, int> Querys[N];

inline void Add(int i, int v) {
    while (i < M) Fen[i] += v, i += i & -i;
}

inline int Sum(int i) {
    int Ret = 0;
    while (i) Ret += Fen[i], i &= i - 1;
    return Ret;
}

inline bool Check(int i, int64 a, int64 b, int64 c) {
    return a * (Points[i].first - D) + b * (Points[i].second - D) + c > 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> Points[i].first >> Points[i].second;
        Points[i].first += D, Points[i].second += D;
    }
    bool Flaga = true, Flagb = true;
    for (int i = 1; i <= m; ++i) {
        std::cin >> std::get<0>(Querys[i]) >> std::get<1>(Querys[i]) >> std::get<2>(Querys[i]);
        Flaga &= !std::get<0>(Querys[i]), Flagb &= !std::get<1>(Querys[i]);
    }
    if (Flaga) {
        std::swap(Flaga, Flagb);
        for (int i = 1; i <= n; ++i) std::swap(Points[i].first, Points[i].second);
        for (int i = 1; i <= m; ++i) std::swap(std::get<0>(Querys[i]), std::get<1>(Querys[i]));
    }
    std::sort(Points + 1, Points + n + 1);
    if (Flagb) {
        int Now = 1, Tmp;
        for (int i = 1; i < M; ++i) {
            Ansl[i] = Ansl[i - 1], Tmp = Now;
            while (Tmp <= n && Points[Tmp].first == i) Ansl[i] += Sum(Points[Tmp++].second - 1);
            while (Now <= n && Points[Now].first == i) Add(Points[Now++].second, 1);
        }
        memset(Fen, 0, sizeof(Fen));
        Now = n;
        for (int i = M - 1; i; --i) {
            Ansr[i] = Ansr[i + 1], Tmp = Now;
            while (Tmp >= 1 && Points[Tmp].first == i) Ansr[i] += n - Now - Sum(Points[Tmp--].second);
            while (Now >= 1 && Points[Now].first == i) Add(Points[Now--].second, 1);
        }
        for (int i = 1; i <= m; ++i) {
            auto [Ta, Tb, Tc] = Querys[i];
            int64 a = Ta, c = -Tc;
            if (a > 0) {
                c += a * D, c = c / a + 1;
                if (c < 0) c = 0;
                if (c >= M) c = M - 1;
                std::cout << Ansr[c] << '\n';
            } else {
                a = -a, c = -c;
                c = (c - 1) / a;
                if (c < 0) c = 0;
                if (c >= M) c = M - 1;
                std::cout << Ansl[c] << '\n';
            }
        }
    } else {
        for (int i = 1; i <= m; ++i) {
            auto [Ta, Tb, Tc] = Querys[i];
            int64 a = Ta, b = Tb, c = Tc, Ans = 0;
            for (int j = 1; j <= n; ++j) {
                int l = j;
                if (Check(l, a, b, c)) Ans += Sum(Points[l].second - 1);
                while (l < n && Points[l].first == Points[l + 1].first) {
                    ++l;
                    if (Check(l, a, b, c)) Ans += Sum(Points[l].second - 1);
                }
                if (Check(j, a, b, c)) Add(Points[j].second, 1);
                while (j < n && Points[j].first == Points[j + 1].first) {
                    ++j;
                    if (Check(j, a, b, c)) Add(Points[j].second, 1);
                }
            }
            std::cout << Ans << '\n';
            memset(Fen, 0, sizeof(Fen));
        }
    }
    return 0;
}