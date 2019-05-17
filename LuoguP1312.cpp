#include <bits/stdc++.h>
class node{
    public:
        int a[10][10];
} empty;
node a[10];
int n;
void dfs(int);
node updata(node, int, int, int, int);  
int operator==(node, node);
int main() {            
    scanf("%d", &n);
    memset(empty.a, 0, sizeof(empty.a));
    for (int i = 1; i <= 5; ++i) {
        for (a[1].a[i][0] = 1; a[1].a[i][a[1].a[i][0] - 1] != 0 && a[1].a[i][0] != 1; ++a[1].a[1][0]) {
            scanf("%d", &a[1].a[i][a[1].a[i][0]]);
        }
        --a[1].a[i][0];
    }
    dfs(1);
    return 0;
}
inline void dfs(int x) {
    if (a[x] == empty) {
        
    }
}
