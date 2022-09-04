#include <bits/stdc++.h>

using uint16 = uint16_t;

const int N = 3005;
const int D = N << 1;
const int M = 1000005;

int n, m;
int Sl[N], Sr[N], Id[M], So[D], IsL[D], IsR[D];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 0; i < n; ++i) std::cin >> Sl[i] >> Sr[i], So[i << 1] = Sl[i], So[i << 1 | 1] = Sr[i];
        std::sort(So, So + n + n);
        m = std::unique(So, So + n + n) - So;
        for (int i = 0; i < m; ++i) Id[So[i]] = i;
        for (int i = 0; i < n; ++i) Sl[i] = Id[Sl[i]], Sr[i] = Id[Sr[i]];
        for (int i = 0; i < n; ++i) std::cout << ':' << Sl[i] << ' ' << Sr[i] << std::endl;
        int Ans = 0;
        for (int i = 0; i < n; ++i) {
            int Il = Sl[i], Ir = Sr[i];
            if (Ir < Il) Ir += m;
            memset(IsL + Il, 0, sizeof(int) * (Ir - Il + 1));
            memset(IsR + Il, 0, sizeof(int) * (Ir - Il + 1));
            int Sum = 0;
            std::cout << "I: " << i << std::endl;
            for (int j = 0; j < n; ++j) {
                int Jl = Sl[j], Jr = Sr[j];
                if (Jl < Il) Jl += m;
                if (Jr < Il) Jr += m;
                int Tr = Jr < Jl ? Jr + m : Jr;
                if (Tr - Jl < Ir - Il) continue;
                if (Jl <= Ir && Jr <= Ir) {
                    ++Sum;
                    std::cout << "J: " << j << " Type " << 1 << std::endl;
                } else if (Jr <= Ir) {
                    ++IsL[Jr];
                    std::cout << "J: " << j << " Type " << 2 << std::endl;
                } else if (Jl <= Ir) {
                    ++IsR[Jl];
                    std::cout << "J: " << j << " Type " << 3 << std::endl;
                } else if (Jr < Jl) {
                    ++Sum;
                    std::cout << "J: " << j << " Type " << 4 << std::endl;
                } else {
                    std::cout << "J: " << j << " Type " << 5 << std::endl;
                }
            }
            for (int j = Ir - 1; j >= Il; --j) IsL[j] += IsL[j + 1];
            for (int j = Il + 1; j <= Ir; ++j) IsR[j] += IsR[j - 1];
            for (int j = Il; j <= Ir; ++j) Ans = std::max(Ans, Sum + IsL[j] + IsR[j]);
        }
        std::cout << Ans << '\n';
    }
    return 0;
}