#include <bits/stdc++.h>
const int N = 100005;
int min, n, plus, x, root, cnt;
int val[N], father[N], lson[N], rson[N], rd[N], size[N];
char ch;
void readw(char &);
void I();
void S();
int find(int);
void dui(int);
int main() {
    srand(15871);
    scanf("%d %d", &n, &min);
    while (n--) {
        readw(ch);
        scanf("%d", &x);
        if (ch == 'A') {
            min -= x;
            plus += x;
        } else if (ch == 'I') {
            I();
        } else if (ch == 'S') {
            min += x;
            plus -= x;
            S();
        } else {
            printf("%d\n", find(root) + plus);
        }
    }
    return 0;
}
inline void readw(char &a) {  // This function helps the programmers to read a
                              // char without ' ', '\n' or '\r'.
    a = getchar();
    while (a == ' ' || a == '\n' || a == '\r') {
        a = getchar();
    }
}
inline void I() {
    if (!cnt) {
        ++cnt;
        size[cnt] = 1;
        rd[cnt] = rand();
        val[cnt] = x;
        return;
    }
    int tmp = root;
    while (1) {
        if (x < val[tmp]) {
            if (!lson[tmp]) {
                ++cnt;
                father[cnt] = tmp;
                val[cnt] = x;
                size[cnt] = 1;
                rd[cnt] = rand();
                lson[tmp] = cnt;
                break;
            } else {
                tmp = lson[tmp];
            }
        } else {
            if (!rson[tmp]) {
                ++cnt;
                father[cnt] = tmp;
                val[cnt] = x;
                size[cnt] = 1;
                rd[cnt] = rand();
                rson[tmp] = cnt;
                break;
            } else {
                tmp = rson[tmp];
            }
        }
    }
    while (tmp) {
        ++size[tmp];
    }
    dui(cnt);
}
inline void S() {
    
}