#include <bits/stdc++.h>
const int N = 100005;
const int C = 26;
int ans, cnt, n, tmp;
int trie[N][C];
std::string s;
void insert(std::string);
void AC(std::string);
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> s;
        insert(s);
    }
    std::cin >> s;
    AC(s);
    printf("%d\n", ans);
    return 0;
}
void insert(std::string s) {
    
}