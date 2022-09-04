#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline std::pair<Type1, Type2> operator-(std::pair<Type1, Type2> a, std::pair<Type1, Type2> b) {
    return std::make_pair(a.first - b.first, a.second - b.second);
}

using int64 = long long;

using Point = std::pair<int, int64>;

const int N = 500005;
const int M = 1000005;

int n, Head;

int64 Red, Ans = INT64_MIN;

Point Po[M], T[M];

inline bool TurnLeft(Point a, Point b) { return a.first * b.second - a.second * b.first >= 0; }
inline bool TurnLeft(Point a, Point b, Point c) { return TurnLeft(b - a, c - b); }

inline int64 Answer(Point a, Point b) { return a.second + b.second - 4ll * a.first * b.first; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1, a, b, x; i <= n; ++i) {
        std::cin >> a >> b >> x;
        Po[(i << 1) - 1] = Point(a, x << 1);
        Po[i << 1] = Point(b, x << 1);
        Red += x * 4ll;
    }
    n <<= 1, Po[++n] = Point(1, 0);
    std::sort(Po + 1, Po + n + 1);
    for (int i = 1; i <= n; ++i) Po[i].second += Po[i - 1].second;
    for (int i = 1; i <= n; ++i) {
        while (Head && TurnLeft(T[Head - 1], T[Head], Po[i])) --Head;
        T[++Head] = Po[i];
    }
    int Now = Head;
    for (int i = 1; i <= n; ++i) {
        while (Now > 1 && Answer(T[Now - 1], Po[i]) > Answer(T[Now], Po[i])) --Now;
        Ans = std::max(Ans, Answer(T[Now], Po[i]) - Red);
    }
    std::cout << Ans << std::endl;
    return 0;
}