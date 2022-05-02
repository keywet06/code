#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

template <typename Type1, typename Type2>
inline Type1 &Mad(Type1 &x, Type2 y) {
    return x > y ? x : (x = y);
}

using int64 = long long;

const int N = 200005;

int n, m, Cnt;
int Num[N << 1];

int64 Ans;

std::vector<std::vector<int> > a;

void Solve(int n, int m, std::function<int(int, int)> A) {
    if (n == 1) return void(++Ans);
    int Rid = n >> 1, Lid = Rid - 1;
    std::vector<std::vector<int> > Max(m, std::vector<int>(n)), Min(Max);
    for (int i = 0; i < m; ++i) {
        Max[i][Lid] = Min[i][Lid] = A(i, Lid);
        Max[i][Rid] = Min[i][Rid] = A(i, Rid);
        for (int j = 0; j < i; ++j) {
            Mad(Max[i][Lid], A(i, Lid)), Mid(Min[i][Lid], A(i, Lid));
            Mad(Max[i][Rid], A(i, Rid)), Mid(Min[i][Rid], A(i, Rid));
        }
        for (int j = 0; j <= i; ++j) {
            std::vector<int> &Ma = Max[j], &Mi = Min[j];
            for (int K = Lid, k = K - 1; k >= 0; --k, --K) Mad(Ma[k], Ma[K]), Mid(Mi[k], Mi[K]);
            for (int K = Rid, k = K + 1; k < n; ++k, ++K) Mad(Ma[k], Ma[K]), Mid(Mi[k], Mi[K]);
            int Len = j - i + 1, K = Rid;
            for (int k = Lid; k >= 0; --k) {
                while (K < n && Min[K] > Min[k]) ++Num[Ma[K] - (K - Lid) * Len], ++K;
                Ans += Num[Mi[k] + (Rid - k) * Len];
                if ((Ma[k] - Mi[k] + 1) % Len == 0) {
                    int c = k + (Ma[k] - Mi[k] + 1) / Len - 1;
                    Ans += c >= Rid && c < n && Ma[c] < Ma[k] && Mi[c] > Mi[c];
                }
            }
            while (K > Rid) --K, --Num[Ma[K] - (K - Lid) * Len];
            K = Lid;
            for (int k = Rid; k < n; ++k) {
                while (K >= 0 && Min[K] > Min[k]) ++Num[Ma[K] - (Rid - K) * Len], --K;
                Ans += Num[Mi[k] + (k - Lid) * Len];
                if ((Ma[k] - Mi[k] + 1) % Len == 0) {
                    int c = k - (Ma[k] - Mi[k] + 1) / Len + 1;
                    Ans += c <= Lid && c >= 0 && Ma[c] < Ma[k] && Mi[c] > Mi[c];
                }
            }
            while (K < Lid) ++K, --Num[Ma[K] - (Rid - K) * Len];
        }
    }
}

inline void Solve(int l, int r, int u, int d) {
    
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    return 0;
}