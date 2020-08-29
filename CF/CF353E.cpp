#include <bits/stdc++.h>
char str[2000001];
unsigned char bv[2000001], indeg[2000001], outdeg[2000001];
int n;
void dfs1(int pt) {
    if (bv[pt]) return;
    bv[pt] = 1;
    if (str[pt] == '0') dfs1((pt + 1) % n);
    if (str[(pt - 1 + n) % n] == '1') dfs1((pt - 1 + n) % n);
}
void dfs2(int pt) {
    if (bv[pt]) return;
    bv[pt] = 1;
    if (str[pt] == '1') dfs2((pt + 1) % n);
    if (str[(pt - 1 + n) % n] == '0') dfs2((pt - 1 + n) % n);
}
int main() {
    std::cin >> str;
    n = strlen(str);
    for (int i = 0; i < n; i++) {
        if (str[i] == '0') {
            indeg[(i + 1) % n]++, outdeg[i]++;
        } else {
            indeg[i]++, outdeg[(i + 1) % n]++;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (bv[i]) continue;
        if (indeg[i] && outdeg[i]) {
            dfs1(i);
            bv[i] = 0;
            dfs2(i);
            ans++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (bv[i]) continue;
        ans++;
        dfs1(i);
        bv[i] = 0;
        dfs2(i);
    }
    std::cout << ans << std::endl;
    return 0;
}