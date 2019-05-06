#include <bits/stdc++.h>
void readw(char &);
void I();
void S();
int find(int);
void xuan(int);
int main() {
    srand(13758);
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
            S();
        } else {
            printf("%d\n", find(root));
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
    int tmp = root;
    for (int i = 1; i <= n; ++i) {
        
    }
}
inline void xuan(int x) {
    
}