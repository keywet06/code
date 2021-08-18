#include <bits/stdc++.h>

const int N = 15;
const int INF = 0x3f3f3f3f;
const int P = 998244353;

int T, n;
char s[N];

inline int add(int a, int b) { return (a += b) >= P ? a - P : a; }
inline int pop(int a, int b) { return (a -= b) < 0 ? a + P : a; }
inline int mul(int a, int b) { return 1LL * a * b % P; }

class matrix {
   public:
    int m[N][N], n;

   public:
    inline matrix() {}

    inline matrix(int n, int o) : n(n) {
        memset(m, 0, sizeof(m));
        for (int i = 1; i <= n; ++i) m[i][i] = o;
    }

    inline matrix operator*(const matrix &o) const {
        matrix c = matrix(n, 0);
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    c.m[i][j] = add(c.m[i][j], mul(m[i][k], o.m[k][j]));
        return c;
    }

    inline void out() {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                printf("%d%c", m[i][j], (j == n ? '\n' : ' '));
            }
        }
        puts("");
    }
};

int main() {
    scanf("%d", &T);
    matrix ans = matrix(4, 0);
    ans.m[1][2] = ans.m[1][4] = 1;
    while (T--) {
        int b;
        scanf("%d%s", &b, s + 1);
        n = strlen(s + 1);
        matrix cur = matrix(4, 1), o = matrix(4, 0);
        for (int i = 1; i <= n; ++i) {
            o = matrix(4, 0);
            if (s[i] == '+') {
                o.m[1][1] = o.m[3][1] = o.m[4][2] = o.m[4][4] = 1;
            } else if (s[i] == '*') {
                o.m[1][1] = o.m[3][2] = o.m[4][4] = 1;
            } else {
                int v = s[i] - '0';
                o.m[1][1] = o.m[2][2] = o.m[4][4] = 1;
                o.m[3][3] = 10, o.m[2][3] = v;
            }
            cur = cur * o;
        }
        while (b) {
            if (b & 1) ans = ans * cur;
            cur = cur * cur, b >>= 1;
        }
    }
    printf("%d\n", add(ans.m[1][1], ans.m[1][3]));
    return 0;
}
