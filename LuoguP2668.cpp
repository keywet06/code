
#include <bits/stdc++.h>
#define fu(i, q, w) for (register int i = q; i <= w; i++)
#define fd(i, q, w) for (register int i = q; i >= w; i--)
using namespace std;
typedef long long ll;
inline int read() {
    int ret = 0, f = 1;
    char c;
    while ((c = getchar()) < '0' || c > '9')
        if (c == '-') f = -1;
    while (c >= '0' && c <= '9') ret = ret * 10 + (c - '0'), c = getchar();
    return ret * f;
}
char word[10];
char check[10];
string numx, numy;
map<char, int> two;
map<char, int> tone;
int n;
void in() {
    n = read();
    cin >> numx;
    fu(i, 1, n - 1) { cin >> numx, word[i] = numx[0]; }
    fu(i, 1, n - 1) fu(j, 1, n) {
        cin >> numx;

        if (j != 1 && j != 2)
            if (numx == numy) {
                printf("ERROR!");
                exit(0);
            }
        numy = numx;
        if (numx.size() == 2) {
            two[word[i]]++;
            tone[numx[1]]++;
        }
    }
}
void solve() {
    fu(i, 1, n - 1) if (two[word[i]] != n - 2 - tone[word[i]]) {
        printf("ERROR!");
        exit(0);
    }

    fu(i, 1, n - 1) cout << word[i] << '=' << two[word[i]] << ' ';
    printf("\n");
    printf("%d", n - 1);
}
int main() {
    in();
    solve();
    return 0;
}