#include <bits/stdc++.h>

const int N = 200005;

char Ca[N], Cb[N];

int Ia[N], Ib[N], Ic[N], Fa[N];

inline int Kmp(char *s, int *Pos, int n) {
    std::vector<int> Fail(n);
    Fail[0] = -1;
    for (int i = 1; i < n; ++i) {
        Fail[i] = Fail[i - 1];
        while (Fail[i] != -1 && s[Fail[i] + 1] != s[i]) Fail[i] = Fail[Fail[i]];
        Fail[i] += s[Fail[i] + 1] == s[i];
    }
    int *Now = Pos;
    for (int x = Fail[n - 1]; x != -1; x = Fail[x]) *Now++ = x + 1;
    return Now - Pos;
}

inline int CKmp(char *s, int *Pos, int *Fail, int n) {
    Fail[0] = -1;
    for (int i = 1; i < n; ++i) {
        Fail[i] = Fail[i - 1];
        while (Fail[i] != -1 && s[Fail[i] + 1] != s[i]) Fail[i] = Fail[Fail[i]];
        Fail[i] += s[Fail[i] + 1] == s[i];
    }
    int *Now = Pos;
    for (int x = Fail[n - 1]; x != -1; x = Fail[x]) *Now++ = x + 1;
    return Now - Pos;
}

inline int GetPos(int *Fail, int *Pos, int n) {
    int *Now = Pos;
    for (int x = Fail[n - 1]; x != -1; x = Fail[x]) *Now++ = x + 1;
    return Now - Pos;
}

inline bool Equal(int *A, int *B, int n) {
    for (int i = 0; i < n; ++i) {
        if (A[i] != B[i]) return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> Ca;
        int n = strlen(Ca), Na = CKmp(Ca, Ia, Fa, n);
        std::reverse(Ia, Ia + Na);
        Ia[Na++] = n;
        memset(Cb, 0, sizeof(Cb));
        if (Ia[0] > 1) Cb[Ia[0] - 1] = 1;
        for (int i = 1; i < Na; ++i) {
            int Lf = Ia[i - 1], Lg = Ia[i];
            for (int i = std::max(Lf, Lg - Lf); i < Lg; ++i) Cb[i] = Cb[Lf + i - Lg];
            if (Lf << 1 >= Lg) continue;
            auto Check = [&]() -> bool {
                int n = GetPos(Fa, Ib, Lg), m = Kmp(Cb, Ic, Lg);
                if (n != m) return false;
                return Equal(Ib, Ic, n);
            };
            while (!Check()) {
                int x = Lg - Lf - 1;
                while (Cb[x]) Cb[x--] = 0;
                Cb[x] = 1;
            }
        }
        for (int i = 0; i < n; ++i) std::cout << int(Cb[i]);
        std::cout << std::endl;
    }
    return 0;
}