#include <bits/stdc++.h>

const char *Subs[25] = {"1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",    "12",   "23",   "45",  "56",
                        "78", "89", "14", "25", "36", "47", "58", "69", "1245", "2356", "4578", "5689"};

const int IdN = 10000;

int Id[IdN];

inline void init() {
    int p[5];
    for (int i = 1; i <= 25; ++i) {
        const char *s = Subs[i - 1];
        int n = strlen(s);
        for (int j = 0; j < n; ++j) p[j] = j;
        do {
            int x = 0;
            for (int j = n - 1; j >= 0; --j) x = x * 10 + s[p[j]] - '0';
            Id[x] = i;
        } while (std::next_permutation(p, p + n));
    }
}

const int N = 100005;

int n;
int S[N], T[N], f[N];

std::string s, t;

inline int Get(int x) { return x; }

template <typename... Args>
inline int Get(int x, Args... args) {
    return x + 10 * Get(args...);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    init();
    std::cin >> n;
    std::cin >> s >> t;
    for (int i = 1; i <= n; ++i) S[i] = s[i - 1] ^ '0', T[i] = t[i - 1] ^ '0';
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        if (i >= 1 && f[i - 1]) {
            x = Id[Get(S[i])];
            y = Id[Get(T[i])];
            f[i] |= x && x == y;
        }
        if (i >= 2 && f[i - 2]) {
            x = Id[Get(S[i], S[i - 1])];
            y = Id[Get(T[i], T[i - 1])];
            f[i] |= x && x == y;
        }
        if (i >= 4 && f[i - 4]) {
            x = Id[Get(S[i], S[i - 1], S[i - 2], S[i - 3])];
            y = Id[Get(T[i], T[i - 1], T[i - 2], T[i - 3])];
            f[i] |= x && x == y;
        }
    }
    std::cout << f[n] << std::endl;
    return 0;
}