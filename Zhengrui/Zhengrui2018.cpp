#include <bits/stdc++.h>

const int B = 2;
const int N = 2005;

char s[N];

int n;

std::bitset<N> tmp;
std::bitset<N> atk[N];
std::bitset<N> f[B][N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s + 1;
        for (int j = 1; j <= n; ++j) atk[i][j] = s[j] - '0';
        f[0][i][i] = f[1][i][i] = 1;
    }
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            tmp = f[0][i] & f[1][j];
            f[1][j][i - 1] = (atk[i - 1] & tmp).any();
            f[0][i][j + 1] = (atk[j + 1] & tmp).any();
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (tmp[i]) std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}